Praktikum 8 - Simulatsioon
====================================

.. include:: ../include/beforethelab.rst

Selles praktikumis teeme tutvust robootika simulatsiooniga. 
Kui varasemalt oleme töötanud füüsilise robotitega, siis tihti on otstarbekam kõigepealt testida oma koodi simulaatoris. 
Käesolevas praktikumis testime oma **kolme varasemat lahendust** kasutades simuleeritud robotit ja maailma. 
Järgnevalt on ette on antud mõned näited, kuid tegelikult võib ise valida need varasemad ülesanded, mida simuleeritud roboti peal katsetada. 
Selles praktikumis pole päris robotit vaja kasutada.

Ülesanne 1
------------------

Käita simulaatori abil oma P-kontrolleriga kaugusehoidmist (7.  praktikumi 2. ülesannet). 

1.  Selleks ava simulaator käsuga

    **roslaunch robotont_description gazebo_teleop_keyboard.launch world:=$(rospack find robotont_description)/worlds/bangbang.world**

2.  Ava uus terminaliaken ning trüki sinna 

    **rosrun robotont_blank_scripts praktikum3_bangbang.py**

3.  Kui robot ei tööta nii nagu peaks, siis ava praktikum3_bangbang.py ja seadista kontrollerit nii, et see ka simulaatoris töötaks.
4.  Demonstreeri töötavat kontrollerit juhendajale.

Ülesanne 2
-------------

Proovime nüüd simulaatoris seinte vahelt läbi sõita. 

1.  Ava terminaliaken ning trüki sinna
    
    **roslaunch robotont_description gazebo_teleop_keyboard.launch world:=$(rospack find robotont_description)/worlds/between.world**

2.  Avanenud aknas saad liigutada robotit lineaarselt soovitud kohta, klikkides robotil ning vajutades vasakul üleval nuppu “Translate mode” või vajutades klahvi “T”. Seejärel tekivad nooled, mida tõmmates liigub robot maailmas.
    
    .. figure:: ../images/lab08/gazebotranslate.png
                :scale: 70 %

                ..

3.  Vajutades vasakul üleval nuppu “Rotation Mode” või klahvi “R”, saab robotit pöörata. Pööramiseks tiri hiirega värvilisi ringe soovitud suunas.
        
    .. figure:: ../images/lab08/gazeborotate.png
                :scale: 70 %

                ..

4.  Roboti liigutamiseks võid ka kasutada klaviatuuri abil juhtimist. Selleks peab aktiivne olema terminaliaken, kus käitasid Gazebo. Kui roboti juhtimiseks kasutavad klahvid on meelest läinud, vaata esimese praktikumijuhendi lõppu.
5.  Kui robot on paigas, käita oma kolmanda praktikumi kood

    **rosrun robotont_blank_scripts praktikum3_betweenposts.py**

6.  Kui robot ei käitu nii nagu peab, proovi muuta oma algoritmi **praktikum3_betweenposts.py** failis.
7.  Demonstreeri töötavat seinte vahelt sõitvat robotit juhendajale.

Ülesanne 3
--------------

Proovime koostada simulaatoris 2D kaarti ja seal navigeerida nagu viiendas praktikumis.

1.  Ava simulaator käsuga
    
    **roslaunch robotont_description gazebo_teleop_keyboard.launch world:=$(rospack find robotont_description)/worlds/mapping.world**

2.  Ava kaardistamislõim käsuga
    
    **roslaunch robotont_teleop teleop_carto_with_navstack_gazebo.launch**

3.  Ava RViz käsuga

    **roslaunch robotont_description display_2dmapping.launch**

4.  Sõida ringi (aktiivne peab olema terminaliaken, kus avasid Gazebo) ning kaardista maailm. Seejärel proovi autonoomselt navigeerida kaardi abil nagu viiendas praktikumis.
5.  Demonstreeri juhendajale.


.. include:: ../include/afterthelab.rst