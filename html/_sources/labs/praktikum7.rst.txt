Praktikum 7 - Regulaatorid
====================================
.. include:: ../include/beforethelabrobot.rst


Praktikumi kirjeldus
-----------------------

Selles praktikumis on lahendada lisaülesanded. Praktikumi läbimiseks pead lahendama vähemalt 3 ülesannet.

Ülesanne 1
------------

Kolmandas praktikumis õppisime tegema bang-bang kontrollerit. Aga sellel kontrolleril on probleem - nimelt kipub kauguse hoidmisel robot edasi-tagasi pendeldama.  
Üks lahendus on suurendada piirkonda, kus kontroller suunda vahetab ning kui anduri näit on selles vahemikus, siis paneme roboti seisma. Seda nimetatakse kolm-punkt regulaatoriks.
Näiteks võib tuua radiaatori ja jahutuse:

- Soovitud temperatuuriks paneme 23 kraadi.
- Hüstereesiks seame 2 kraadi.
- Kui temperatuur on alla 22 kraadi, on radiaator sees, jahutus väljas.
- Kui temperatuur on 22-24 kraadi, on radiaator ja jahutus väljas.
- Kui temperatuur läheb üle 24 kraadi, on radiaator välja ja jahutus sees.

Selline implementatsioon väldib olukorda, kus radiaator jääks end kiiresti 23 kraadi juures sisse-välja klõpsima. 
Ülesanne on teha samasugune kolm-punkt regulaator, mis hoiab robotit umbes 0,6 meetri kaugusel seinast. 
Hüstereesi suuruse võid ise valida, et saavutada parim võimalik lahendus.

**Ülesanne**

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Terminaliaknas sisesta 

    **roslaunch robotont_teleop teleop_with_laserscan.launch**

3.  Ava uus terminaliaken ning loo ssh-ühendus robotisse
4.  Terminaliaknas sisesta 
    
    **nano catkin_ws/src/robotont_blank_scripts/scripts/praktikum3_bangbang.py**

5.  Selles failis peaks olema su kolmanda praktikumi bang-bang kontroller ehk kaks-punkt regulaator. Ülesanne on muuta koodi, et see oleks kolm-punkt regulaator.
6.  Koodi käitamiseks sisesta terminali
    
    **rosrun robotont_blank_scripts praktikum3_bangbang.py**
    
    Ctrl+C paneb programmi kinni.

7.  Demonstreeri töötavat kontrollerit juhendajale.

Ülesanne 2
------------

Kolm-punkt regulaatori puhul on probleem, et tulemus on ebatäpne. 
Roboti tegelik kaugus kogu hüstereesiga määratud vahemikus on pole teada. Selleks, et olukorda natuke parandada, saab kasutada proportsionaalset kontrollerit ehk P-kontroller. 
Selle mõtet võib illustreerida roboti puhul näiteks nõnda, et mida lähemal oleme soovitud kaugusele, seda aeglasemalt sõidame. 
Ja vastupidiselt, kui robot paikneb soovitud punktist väga kaugel, siis võib liikuda kiiremini. Lühidalt: roboti kiirus on proportsionaalne kaugusega sihtpunktist. 
Matemaatiliselt võib seda kirjutada kui 

.. math::

   v = Kp\cdot e


kus v on kiirus, millega robot sõidab, Kp on enda seatud konstant, mis määrab kuidas kontroller toimib ja e on viga soovitud kauguse ning praeguse kauguse vahel.
    
    .. figure:: ../images/lab07/pcontroller.png
                :scale: 70 %

                ..

**Ülesanne**

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Terminaliaknas sisesta 
    
    **roslaunch robotont_teleop teleop_with_laserscan.launch**

3.  Ava uus terminaliaken ning loo ssh-ühendus robotisse
4.  Terminaliaknas sisesta 
    
    **nano catkin_ws/src/robotont_blank_scripts/scripts/praktikum3_bangbang.py** 

5.  Kommenteeri koodist välja oma varasem kolm-punkt regulaator ning kirjelda roboti juhtimiseks proportsionaalne kontroller, mis hoiab robotit seinast 0,6 m kaugusel. 
6.  Koodi käitamiseks sisesta terminali
    
    **rosrun robotont_blank_scripts praktikum3_bangbang.py**

    Ctrl+C paneb programmi kinni.

7.  Demonstreeri töötavat kontrollerit juhendajale.

Ülesanne 3
------------

Ülesannetes 1 ja 2 tutvustatud kontrollereid saab nüüd kasutada, et teha paremaks neljandas praktikumis tehtud AR markerite jälgimine. 
Ülesanne on muuta oma AR-märgiste jälgimise programm sujuvamaks, kasutades proportsionaalset regulaatorit.

**Ülesanne**

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Terminaliaknas sisesta 

    **roslaunch robotont_training robotont_ar.launch**

3.  Ava uus terminal, loo ssh-ühendus ning seal ava praktikum4_ar.py fail, kasutades käsku
    
    **nano catkin_ws/src/robotont_blank_scripts/scripts/praktikum4_ar.py**

4.  Otsi koodis kommentaar “CHANGE THIS NUMBER TO YOUR MARKER ID” ja selle rea all muuda **marker.id** == väärtus end markerile vastavaks
5.  Muuda kõiki kolme funktsiooni nii, et need kasutaks P-kontrollerit.
6.  Nanost väljumiseks Ctrl+X, salvesta ja skripti saad jooksutada käsuga
    
    **rosrun robotont_blank_scripts praktikum4_ar.py**

    Ctrl+C, et skript peatada.

7.  Demonstreeri töötavat kontrollerit juhendajale.
8.  Robot peab olema võimeline sõitma teise roboti järel. 




.. include:: ../include/afterthelabrobot.rst