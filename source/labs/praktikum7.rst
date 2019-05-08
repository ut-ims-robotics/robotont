Praktikum 7 - regulaatorid
====================================
.. include:: ../include/beforethelabrobot.rst


Praktikumi kirjeldus
-----------------------

Selles praktikumis on lahendada lisaülesanded. Praktikumi läbimiseks pead lahendama vähemalt 3 ülesannet.

Ülesanne 1
------------

Kolmandas praktikumis õppisime tegema bang-bang kontrollerit. Aga sellel kontrolleril on probleem - nimelt kipub kauguse hoidmisel robot edasi-tagasi pendeldama.  
Üks lahendus on suurendada piirkonda, kus kontroller suunda vahetab. Seda nimetatakse kui bang-bang kontroller hüstereesiga.
Näiteks võib tuua radiaatori:

- Soovitud temperatuuriks paneme 23 kraadi.
- Hüstereesiks seame 2 kraadi.
- Seega kui radiaator on sees, siis välja lülitab ta end kui temperatuur on läinud üle 24 kraadi.
- Sisse tagasi lülitab radiaator end siis, kui temperatuur on langenud alla 22 kraadi.

Selline implementatsioon väldib olukorda, kus radiaator jääb end kiiresti 23 kraadi juures sisse-välja klõpsima. 
Ülesanne on teha samasugune hüstereesiga bang-bang kontroller, mis hoiab robotit umbes 0,6 meetri kaugusel seinast. 
Hüstereesi suuruse võid ise valida, et saavutada parim võimalik lahendus.

**Ülesanne**

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Terminaliaknas sisesta 

    **roslaunch robotont_teleop teleop_with_laserscan.launch**

3.  Ava uus terminaliaken ning loo ssh-ühendus robotisse
4.  Terminaliaknas sisesta 
    
    **nano catkin_ws/src/robotont/robotont_blank_scripts/scripts/praktikum3_bangbang.py**

5.  Selles failis peaks olema su kolmanda praktikumi bang-bang kontroller. Ülesanne on muuta koodi, et see oleks hüstereesiga bang-bang kontroller.
6.  Koodi käitamiseks sisesta terminali
    
    **rosrun robotont_blank_scripts praktikum3_bangbang.py**
    
    Ctrl+C paneb programmi kinni.

7.  Demonstreeri töötavat kontrollerit juhendajale.

Ülesanne 2
------------

Hüstereesiga *bang-bang* kontrolleri puhul on probleem, et tulemus on ebatäpne. Roboti tegelik kaugus kogu hüstereesiga määratud vahemikus on pole teada. Selleks, et olukorda natuke parandada, saab kasutada proportsionaalset kontrollerit ehk P-kontroller. Selle mõtet võib illustreerida roboti puhul näiteks nõnda, et mida lähemal oleme soovitud kaugusele, seda aeglasemalt sõidame. Ja vastupidiselt, kui robot paikneb soovitud punktist väga kaugel, siis võib liikuda kiiremini. Lühidalt: roboti kiirus on proportsionaalne kaugusega sihtpunktist. Matemaatiliselt võib seda kirjutada kui 

.. math::

   v = Kp\cdot e


kus v on kiirus, millega robot sõidab, Kp on enda seatud konstant, mis määrab kuidas kontroller toimib ja e on viga soovitud kauguse ning praeguse kauguse vahel.

**Ülesanne**

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Terminaliaknas sisesta 
    
    **roslaunch robotont_teleop teleop_with_laserscan.launch**

3.  Ava uus terminaliaken ning loo ssh-ühendus robotisse
4.  Terminaliaknas sisesta 
    
    **nano catkin_ws/src/robotont/robotont_blank_scripts/scripts/praktikum3_bangbang.py** 

5.  Kommenteeri koodist välja oma varasem (hüstereesiga) bang-bang kontroller ning kirjelda roboti juhtimiseks  proportsionaalne kontroller, mis hoiab robotit seinast 0,6 m kaugusel. 
6.  Koodi käitamiseks sisesta terminali
    
    **rosrun robotont_blank_scripts praktikum3_bangbang.py**

    Ctrl+C paneb programmi kinni.

7.  Demonstreeri töötavat kontrollerit juhendajale.

Ülesanne 3
------------

Ülesannetes 1 ja 2 tutvustatud kontrollereid saab nüüd kasutada, et teha paremaks neljandas praktikumis tehtud AR markerite jälgimine. 
Ülesanne on muuta oma AR-märgiste  jälgimise programm sujuvamaks kasutades kas proportsionaalset või hüstereesiga *bang-bang* kontrollerit.

**Ülesanne**

1.  Ava uus terminal, loo ssh-ühendus ning seal ava praktikum4_ar.py fail, kasutades käsku
    
    **nano catkin_ws/src/robotont/robotont_blank_scripts/scripts/praktikum4_ar.py**

2.  Otsi koodis kommentaar “CHANGE THIS NUMBER TO YOUR MARKER ID” ja selle rea all muuda **marker.id** == väärtus end markerile vastavaks
3.  Muuda kõiki kolme funktsiooni nii, et need kasutaks P-kontrollerit.
4.  Nanost väljumiseks Ctrl+X, salvesta ja skripti saad jooksutada käsuga
    
    **rosrun robotont_blank_scripts praktikum4_ar.py**

    Ctrl+C, et skript peatada.

5.  Demonstreeri töötavat kontrollerit juhendajale.
6.  Robot peab olema võimeline sõitma teise roboti järel. 




.. include:: ../include/afterthelabrobot.rst