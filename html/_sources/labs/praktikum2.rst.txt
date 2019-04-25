Praktikum 2 - Programmeerimise alused: for-tsükkel, funktsioonid
===================================================================

Giti üles seadmine
------------------------

Git on versioonihaldustarkvara, mis aitab meil salvestada koodi internetti, et seda ka hiljem kasutada saaks, kui arvutist kood kustutatud on.

1.  Mine lehele https://github.com/ ning registreeri ennast kasutajaks.
2.  Logi sisse
3.  Mine lehele https://github.com/ut-ims-robotics/robotont_blank_scripts
4.  Vajuta paremal üleval nuppu “Fork”, see kopeerib selle repositooriumi sinu kasutajasse.
5.  Vajuta rohelist nuppu “Clone or download”
6.  Kopeeri sealt aadress
7.  Ava terminal ning trüki sinna

    **cd catkin\_ws/src**

8.  Seejärel sisesta

    **git clone \-sinu\-kopeeritud\-link\-**

9.  Nüüd trüki terminali

    **catkin build**

10. Kui see protsess on lõpetanud edukalt, sulge terminal ja oled valmis praktikumiga jätkama.

Sissejuhatus
-------------------

Selles praktikumis kirjutame programmi, mis paneb roboti sõitma. 
Selleks kasutame programmeerimiskeelt Python. 
Selles praktikumis kasutame roboti liigutamiseks for-tsükleid ning funktsioone. 
Kui Pythoni kasutamine on meelest läinud või sa pole seda kunagi osanudki, siis tuleb abiks Tartu Ülikooli arvutiteaduste instituudi `programmeerimisõpik <https://progeopik.cs.ut.ee/index.html>`_.

ROS-rubriigid
---------------------

ROSis ehk roboti operatsioonisüsteemis töötavad samal ajal erinevad sõlmed ehk konkreetsele ülesandele pühendatud programmid. 
Näiteks on sõlm, mis suhtleb kaameraga ja saab sealt pildi. Või on sõlm, mis paneb roboti rattad soovitud suunas liikuma. 
Samuti sõlm, kust saad robotit klaviatuuri abil juhtida.
Selleks, et kogu robot ühtsena töötaks, peavad need sõlmed omavahel suhtlema. 
Näiteks sõlm, mis paneb rattad liikuma, peab teadma kuhu suunas rattad liikuma panna ning see informatsioon tuleb sõlmelt, kus saad klaviatuuriga robotit juhtida.
Suhtlemiseks on ROSis kasutusel ROS-rubriigid. 
Rubriigil on oma nimi ning sõlmed saavad sinna sõnumeid kuulutada ning sealt tellida. 
Selles praktikumis kasutame rubriiki nimega “cmd_vel” (velocity command), kuhu saame kuulutada, kuhu poole robot liikuma peaks, ning samaaegselt tellib see sõlm, mis rattaid liigutab, sealt käske ning vastavalt neile liigutab robotit.

Teema cmd_vel ja kuidas seda muuta?
---------------------------------------

Selleks, et robot liikuma hakkaks, peame sellele edastama info, kui kiiresti ja mis suunas liikuda. 
Selleks on meile muutmiseks saadaval kolm argumenti: x-suunaline kiirus, y-suunaline kiirus ja z-telje ümber pöörlemiskiirus. 

.. figure:: ../images/lab02/coord.png
            :scale: 70 %

            ..

Positiivsed x’i väärtused panevad roboti edasi sõitma, negatiivsed tagurpidi.
Positiivsed y’i väärtused panevad roboti vasakule sõitma, negatiivsed paremale.
Positiivsed z’i väärtused panevad roboti vastupäeva pöörlema, negatiivsed päripäeva.
x ja y väärtused on ühikutes *m/s*, seega hoia need alla ühe.

Etteantud näidiskoodis on võimalus muuta kõiki kolme argumenti. 
Esimene eesmärk on aru saada, kuidas need töötavad, et oskaks hiljem neid kasutada ka keerukamatel juhtudel.
Leia koodis see koht ning muutes x, y ja z väärtusi, lahenda järgnevad ülesanded.

.. code-block:: python

    vel_msg.linear.x = 0
    vel_msg.linear.y = 0
    vel_msg.angular.z = 0
    velocity_publisher.publish(vel_msg)
    rospy.sleep(0.1)

Ülesanne - cmd_vel
~~~~~~~~~~~~~~~~~~~~

1.  Ava terminal

.. ja tee ssh-ühendus robotisse
.. .. toggle-header::
..     :header: **Kui töötad simulatsioonis**

..         Kui töötad simulatsioonis, siis ava lihtsalt terminal.

2.  Trüki terminali

    **nano catkin_ws/src/robotont_blank_scripts/scripts/praktikum2_move.py**

    See avab Python’i faili, kus hakkame väärtusi muutma. 
3.  Koodis on ära märgitud ala, mida pead muutma. 
    Muuta võid ainult ala, mis on “YOUR CODE HERE START” ja “YOUR CODE HERE END” vahel. 
    Esialgu, muuda *vel_msg.linear.x* väärtus 0.2ks.

    .. figure:: ../images/lab02/yourcodehere.png
            :scale: 70 %

            ..

4.  Salvesta ning välju. Kas mäletad kuidas seda teha? Kui ei, siis vaata esimese praktikumi juhendist järele.
5.  Nüüd ava uus terminal ning loo ssh-ühendus robotisse.

.. .. toggle-header::
..     :header: **Kui töötad simulatsioonis**

..         Kui töötad simulatsioonis, siis ava lihtsalt terminal ning simulatsiooni käitamiseks kasuta käsku

..         **roslaunch robotont_description gazebo.launch**
        
..         ja mine punktini 7.

6.  Uues terminalis sisesta 

    **roslaunch robotont_teleop teleop_bare.launch**

    See paneb käima ROSi draiveri, mis kontrollib rataste kiirusi vastavalt meie sõnumitele.
7.  Eelmises (arvuti)terminalis sisesta 

    **rosrun robotont_blank_scripts praktikum2_move.py**

    See paneb roboti sõitma. Peatamiseks vajuta samas terminalis korraga klahve **Ctrl + C**.
8.  Kui robot sõitis otse, siis jätka, kui ei sõitnud, mõtle, mis võis valesti olla. Kui välja ei mõtle, siis kutsu juhendaja.
9.  Nüüd, kui tutvus on tehtud, proovime ise robotit liigutada. **Iga ülesande järel kirjuta üles oma x, y ja z väärtused**.

    a.  Pane robot sõitma tagasi.
    b.  Pane robot sõitma vasakule/paremale.
    c.  Pane robot pöörama vasakule/paremale.
10. Pane robot sõitma 45 kraadise nurga all.
11. Pane robot kaares sõitma
12. Pane robot ringis sõitma

For-tsükkel, sõidame nelinurka
-------------------------------------------
Eelmiste ülesannete juures andsime robotile ainult ühe käsu, mille järgi ta siis sõitis. Aga mis siis, kui tahame näiteks alguses otse sõita ja siis paremale ning jälle otse ja paremale ja korrata neid erinevaid käske?
Selleks on programmeerimises olemas tsüklid. *while*-tsüklit, ehk lõpmatut tsüklit kasutasid juba tegelikult eelmistes ülesannetes. Kiiruse muutmise käsku edastati robotile korduvalt, seni kuni kood käis. 
Robotile on turvalisuse eesmärgil sisse ehitatud nn *failsafe*, mis jätab roboti seisma, kui poole sekundi jooksul käsku ei tule. 
Nüüd tahame aga öelda talle ühte käsku kindel arv kordi ja siis teist käsku kindel arv kordi. Siinkohal tuleb appi `for-tsükkel <https://progeopik.cs.ut.ee/07_listid.html>`_.
*for*-tsükkel jooksutab käske täpselt nii palju, kui sellele öelda.
Pythonis saame seda kasutada nii:

.. code-block:: python

    for i in range(0,30):
      vel_msg.linear.x = 0.2
      vel_msg.linear.y = 0
      vel_msg.angular.z = 0
      velocity_publisher.publish(vel_msg)
      rospy.sleep(0.1)

See kood ütleb iga 0.1 sekundi tagant robotile, et ta sõidaks edasi kiirusega 0.2 *m/s* ja seda täpselt 30 korda.

Kui me lisame teise *for*-tsükli sinna otsa, siis järgmised 30 korda öeldakse robotile, et ta sõidaks kiirusega 0.2 *m/s* tagasi.

.. code-block:: python

    for i in range(0,30):
      vel_msg.linear.x = 0.2
      vel_msg.linear.y = 0
      vel_msg.angular.z = 0
      velocity_publisher.publish(vel_msg)
      rospy.sleep(0.1)
    for i in range(0,30):
      vel_msg.linear.x = -0.2
      vel_msg.linear.y = 0
      vel_msg.angular.z = 0
      velocity_publisher.publish(vel_msg)
      rospy.sleep(0.1)

Nii saab erinevaid käske üksteise otsa lisada. Muutes “range(0,30)” käsus numbrit 30, saame muuta kui pikalt ühte käsku täidetakse. 

Ülesanne - for-tsükkel
~~~~~~~~~~~~~~~~~~~~~~~~~~

1.  Ülesanne on panna robot ruutu sõitma

    a.  Selleks pead tegema alguses ühe *for*-tsükli, mis sõidab otse mingi maa, millest saab ruudu külje pikkus.
    b.  Selle tsükli järel peaks olema teine tsükkel, mis pöörab robotit 90 kraadi (pead leidma sobiva kiiruse ja tsükli pikkuse kombinatsiooni).
    c.  Kuna need tsüklid on suuremas *while*-tsüklis, siis sellest peakski piisama ning robot sõidab igavesti ruutu.
2.  Ava terminal ning loo ssh-ühendus robotisse.
3.  Ava **nano**'ga fail **praktikum2_forloop.py**, kasutades analoogset käsku nagu eelmises ülesandes.
4.  Koodis on ära märgitud ala, mida pead muutma.
5.  Kui oled vahepeal draiveri terminali sulgenud, siis jätka punktiga a. Kui see eelmisest ülesandest veel käib, mine otse punkti juurde nr 6.

    a.  Ava uus terminal ning loo ssh-ühendus robotisse.
    b.  Uues terminalis sisesta 

        **roslaunch robotont_teleop teleop_bare.launch**

        nagu ka eelmises ülesandes.
6.  Koodi jooksutamiseks kasuta analoogset **rosrun** käsku nagu eelmises ülesandes, kuid vaheta failinimi, mida jooksutad. Peatamiseks vajuta samas terminalis korraga klahve **Ctrl + C**.


Funktsioonid
-----------------

Selleks, et meil oleks kergem koodi kirjutada ja et me ei peaks koodi kopeerima, on olemas funktsioonid. 
Korduva koodi saame kirjutada funktsioonide sisse ning funktsiooni ühe reaga välja kutsuda. 
See parandab koodi loetavust ning teeb edasise programmeerimise lihtsamaks. 
Funktsioonide kohta saab lugeda `progeõpikust <https://progeopik.cs.ut.ee/04_funktsioonid.html>`_. 
Järgneva ülesande eesmärk on kirjutada funktsioonid erimoodi sõitmiseks, et hiljem oleks lihtne ühe käsuga panna robot soovitud suunas sõitma.

Ülesanne - funktsioonid
~~~~~~~~~~~~~~~~~~~~~~~~~~

1.  Ava terminal ning loo ssh-ühendus robotisse.
2.  Ava **nano**'ga fail **praktikum2_functions.py**, kasutades analoogset käsku nagu eelmises ülesandes.
3.  Koodis on ära märgitud alad, mida pead muutma. PS: Funktsioon peab analoogselt eelmise ülesandega lõppema kuulutamisega (publish) ning ootamisega (sleep).
4.  Kui oled vahepeal draiveri terminali sulgenud, siis jätka punktiga a. Kui see eelmisest ülesandest veel käib, mine otse punkti juurde nr 5.

    a.  Ava uus terminal ning loo ssh-ühendus robotisse.
    b.  Uues terminalis sisesta 

        **roslaunch robotont_teleop teleop_bare.launch**
       
5.  Koodi jooksutamiseks kasuta analoogset **rosrun** käsku nagu eelmises ülesandes, kuid vaheta failinimi, mida jooksutad. Peatamiseks vajuta samas terminalis korraga klahve **Ctrl + C**.
6.  Implementeeri funktsioon otse sõitmiseks.

    a.  argumentideks peavad olema kestus (mitu korda *for*-tsüklit kordad) ja kiirus
    b.  katseta oma funktsiooni

7.  Implementeeri funktsioon pööramiseks.

    a.  argumentideks peavad olema kestus (mitu korda *for*-tsüklit kordad) ja kiirus
    b.  katseta oma funktsiooni

8.  Implementeeri funktsioon küljele sõitmiseks.

    a.  argumentideks peavad olema kestus (mitu korda *for*-tsüklit kordad) ja kiirus
    b.  katseta oma funktsiooni

9.  Kasutades neid funktsioone, pane robot sõitma mööda oma valitud kujundit.


.. include:: ../include/afterthelab.rst