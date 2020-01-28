#include "robotont_driver/robotont_hardware.h"

namespace robotont
{
RobotontHW::RobotontHW()
{
  ROS_DEBUG("Robotont driver is starting...");

  // Get parameters from ROS parameter server
  std::string robotont_port;
  int robotont_baudrate;
  std::string odom_frame;
  std::string odom_child_frame;

  nh_.param("serial/port", robotont_port, std::string("/dev/ttyACM0"));    
  nh_.param("serial/baudrate", robotont_baudrate, 115200);    
  nh_.param("odom/frame", odom_frame, std::string("odom"));    
  nh_.param("odom/child_frame", odom_child_frame, std::string("base_footprint"));    

  // configure serial
  serial_.setPort(robotont_port);
  serial_.setBaudrate(robotont_baudrate);
  serial::Timeout timeout = serial::Timeout::simpleTimeout(1000);
  serial_.setTimeout(timeout);

  // Configure odom frames
  odom_.setFrameId(odom_frame);
  odom_.setChildFrameId(odom_child_frame);

  connect();
  // Port is open, ready to communicate.

  // Create a timer to periodically read data from the serial buffer
  timer_ = nh_.createTimer(ros::Duration(0.01), &RobotontHW::read, this);

  // Subscribe to command velocity topic
  cmd_vel_sub_ = nh_.subscribe("cmd_vel", 1, &RobotontHW::cmd_vel_callback, this);
}

void RobotontHW::connect()
{
  if (serial_.isOpen())
  {
    // Connection already open, close it before reconnecting
    serial_.close();
  }

  do
  {
    // Try to open the serial port
    try
    {
      serial_.open();
    }
    catch (serial::IOException e)
    {
      ROS_ERROR_STREAM("Unable to open port '" << serial_.getPort() << "': " << e.what());
    }
    catch (serial::SerialException e)
    {
      ROS_ERROR_STREAM("Unable to open port '" << serial_.getPort() << "': " << e.what());
    }

    if (serial_.isOpen())
      ROS_DEBUG_STREAM("Connected to serial port '" << serial_.getPort() << "'");
    else
      ROS_WARN("Failed to open Serial port, retrying after 1 sec...");
    ros::Duration(1).sleep();
  } while (!serial_.isOpen() && ros::ok());
}

RobotontHW::~RobotontHW()
{
  std::string packet = "\x1B";
  write(packet);
}

void RobotontHW::read(const ros::TimerEvent& event)
{

  std::string buffer = "";

  try
  {
    size_t bytes_available = serial_.available();
    //  ROS_DEBUG("bytes available: %lu", bytes_available);
    if (!bytes_available)
    {
      return;
    }

    serial_.read(buffer, bytes_available);
  }
  catch(serial::IOException e)
  {
    connect();
  }
  catch(serial::SerialException e)
  {
    connect();
  }

  while(buffer.size())
  {
    if(buffer[0] == '\r' || buffer[0] == '\n')
    {
      processPacket();
      packet_ = "";
    }
    else
    {
      packet_.push_back(buffer[0]);
    }

    buffer.erase(buffer.begin());
  }
}


void RobotontHW::processPacket()
{

  if(packet_.length() <= 2)
  {
    return;
  }

  std::stringstream ss(packet_);
  std::string arg[7];
  std::getline(ss, arg[0], ':');

  // parse motor speeds packet format [SPEED:speed_m0:speed_m1:speed_m2]
  if (arg[0] == "ODOM")
  {
    for (int i = 1; i < 7; i++)
    {
      std::getline(ss, arg[i], ':');
      if (!arg[i].length())
      {
        return;  // invalid packet
      }
    }

    float pos_x = atof(arg[1].c_str());
    float pos_y = atof(arg[2].c_str());
    float ori_z = atof(arg[3].c_str());
    float lin_vel_x = atof(arg[4].c_str());
    float lin_vel_y = atof(arg[5].c_str());
    float ang_vel_z = atof(arg[6].c_str());

    odom_.update(pos_x, pos_y, ori_z, lin_vel_x, lin_vel_y, ang_vel_z);
    odom_.publish();
  }
}

void RobotontHW::writeMotorSpeed(float speed_m1, float speed_m2, float speed_m3)
{
  std::stringstream ss;
  ss << "MS:";
  ss << speed_m1 << ":";
  ss << speed_m2 << ":";
  ss << speed_m3 << "\r\n";
  write(ss.str());
}

void RobotontHW::writeRobotSpeed(float lin_vel_x, float lin_vel_y, float ang_vel_z)
{
  std::stringstream ss;
  ss << "RS:";
  ss << lin_vel_x << ":";
  ss << lin_vel_y << ":";
  ss << ang_vel_z << "\r\n";
  write(ss.str());
}

void RobotontHW::write(const std::string& packet)
{
  try
  {
    serial_.write(packet);
  }
  catch(serial::IOException e)
  {
    connect();
  }
  catch(serial::SerialException e)
  {
    // something went wrong, make sure we're connected
    // TODO: maybe not the best style to reconnect here as this will block the callback until reconnected
    // (same pattern in read())
    connect();
  }
}

void RobotontHW::cmd_vel_callback(const geometry_msgs::Twist& cmd_vel_msg)
{
//  ROS_INFO_STREAM("I heard: \r\n" << cmd_vel_msg);
  writeRobotSpeed(cmd_vel_msg.linear.x, cmd_vel_msg.linear.y, cmd_vel_msg.angular.z);
}

  /*

  float vel_x = cmd_vel_msg.linear.x;
  float vel_y = -cmd_vel_msg.linear.y;
  float vel_t = cmd_vel_msg.angular.z;

  int motorCount = wheelAmount;

  float robotSpeed = 0;

  if (vel_x == 0)
  {
    robotSpeed = std::abs(vel_y);
  }
  else if (vel_y == 0)
  {
    robotSpeed = std::abs(vel_x);
  }
  else
  {
    robotSpeed = sqrt(vel_x * vel_x + vel_y * vel_y);
  }

  float robotDirectionAngle = atan2(vel_x, vel_y);

  // ROS_INFO_STREAM("robotDirectionAngle: " << (float)wheelAngles[0]); //debug purpouse

  float robotAngularVelocity = -vel_t * angular_vel_scaler;

  float wheelLinearVelocity[motorCount];
  float wheelAngularSpeedMainboardUnits[motorCount];

  for (int i = 0; i < motorCount; i++)
  {
		wheelLinearVelocity[i] = robotSpeed * cos(robotDirectionAngle - wheelAngles[i]) + wheelDistanceFromCenter * robotAngularVelocity;
		wheelAngularSpeedMainboardUnits[i] = wheelLinearVelocity[i] * wheelSpeedToMainboardUnits;
    }


    if (vel_x == 0 and vel_y == 0 and vel_t == 0){
		m0 = m1 = m2 = 0;
		output_cmd = "\x1B\r\n"; //send ESC, which means stop
    }
    else {
		m0 = wheelAngularSpeedMainboardUnits[0] * wheel_ang_scaler;
		m1 = wheelAngularSpeedMainboardUnits[1] * wheel_ang_scaler;
		m2 = wheelAngularSpeedMainboardUnits[2] * wheel_ang_scaler;
		std::stringstream sstm;
		//    sstm << 'a' << static_cast<int>(m0) << 'b' << static_cast<int>(m1) << 'c' << static_cast<int>(m2) << '\n'; // for previous firmware implementation
		sstm << static_cast<int>(m0) << ':' << static_cast<int>(m1) << ':' << static_cast<int>(m2) << '\r' <<'\n';
    }
*/

}  // namespace robotont
