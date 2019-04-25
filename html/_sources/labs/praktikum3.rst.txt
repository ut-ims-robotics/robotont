Praktikum 3 - Andurid, if-lause, bang-bang kontroller
========================================================
.. include:: ../include/beforethelabrobot.rst

Mis andurid on Clearbotil?
-----------------------------

Clearbotil on peal Realsense D435 3D kaamera, millest saab tavalise kaamerapildi ja sügavuspildi.
Käesolevas praktikumis kasutame 3D kaamerast sügavuspildi andmeid. Aga mitte toorelt. 
Nimelt on 3D sügavuspildist võetud ainult üks riba ning tehtud sellest 2D laserskann. 
See laserskann on omakorda jagatud kolmeks ja võetud minimaalsed takistuste kaugused paremal, keskel ja vasakul.

.. figure:: ../images/lab03/gridlaserscan.png
            :scale: 70 %

            ..

Samuti on roboti ratastel enkoodrid, mis mõõdavad, kui palju ratas on liikunud, kuid seda me veel siin praktikumis ei kasuta.

Mis on kontroller?
--------------------
Eelmises lõigus tutvustati, mis on andurid. 
Nüüd on vaja ka teada, kuidas saame liigutada robotit sõltuvalt andurite näidust. 
Selleks on olemas kontrollerid. 
Kontrollerite ülesanne on sõltuvalt sisendist, näiteks andurite näidust, 
muuta väljundit, näiteks mootorite kiirust. 
Näiteks auto püsikiirusehoidja mõõdab kiirust ning annab selle järgi erinevalt gaasi. 
Kui kiirus on väiksem kui soovitud, annab kontroller gaasi 
ning kui kiirus on suurem kui soovitud, siis laseb gaasi lahti. 
Ka selles praktikumis kirjutame ise kontrolleri.

Kui kaugel on meist eespool paiknevad asjad?
------------------------------------------------

Selleks, et teada, kui kaugel on lähim asi vasakul, keskel ja paremal, 
saame tellida ROS rubriiki “/scan_to_distance”, mis annab meile laserskannist arvutatud väärtused.

1.  Ava terminal ning loo ssh-ühendus robotisse.
2.  Kirjuta sinna

    **roslaunch robotont_teleop teleop_with_laserscan.launch**

    Kui väljund on väga punane, kutsu juhendaja
3.  Nüüd ava uus terminal
4.  Selleks, et vaadata, mis andmeid robot meile annab, kasutame terminalis käsku 

    **rostopic echo /scan_to_distance**

    .. figure:: ../images/lab03/terminal.png
            :scale: 70 %

            ..

    *leftMin*, *centerMin* ja *rightMin* näitavad minimaalset kaugust igas sektoris. Ühikuks on meeter.

5.  Liiguta oma kätt kaamera ees ning jälgi kuidas väärtused muutuvad.

Nüüd kui oleme aru saanud, kuidas need kaugused töötavad, on aeg neid kasutada.

Proovime asjadele mitte otsa sõita
-------------------------------------

**Võtame lahti faili, kuhu hakkame koodi kirjutama**

1.  Ava terminal ning loo ssh-ühendus robotisse.
2.  Trüki terminali 

    **nano catkin_ws/src/robotont_blank_scripts/scripts/praktikum3_bangbang.py**

    See avab Python’i faili, kus hakkame väärtusi muutma.

Selleks, et me Python’is näeksime ja saaksime kasutada neid kaugusi, on meil muutuja nimega *distances*. 
Sellel muutujal on meie jaoks olulised kolm väärtust, 
mis on tabelis välja toodud.

    .. figure:: ../images/lab03/tabel.png
            :scale: 100 %

            ..

Esialgu kasutame ainult *distances.centerMin* muutujat ning teeme robotile *bang-bang* kontrolleri. 
*Bang-bang* kontroller ehk eestikeeli kaks-punkt reguleerimine on automaatreguleerimine, 
kus lülitatakse seadet kahe oleku vahel, olenevalt anduri näidust. 
Näiteks kui toas on liiga külm, lülitab radiaator end sisse, kui temperatuur on normis või üle, 
lülitab end välja.

Meie robotiga kasutame *bang-bang* kontrollerit nõnda:

- Vaatame kui lähedal on eesolev asi

- Kui asi on piisavalt kaugel või takistus puudub, sõidame otse

- Kui asi on liiga lähedal, tagurdame

**Ülesanne**

1.  Ava uus terminal ning loo samuti ssh-ühendus robotisse.
2.  Terminalis sisesta 

    **roslaunch robotont_teleop teleop_with_laserscan.launch**

    See paneb käima ROSi draiveri, mis kontrollib rataste kiirusi vastavalt meie sõnumitele ning annab ka andmeid eesolevate takistuste kohta.

3.  Kasutades **if-else**-lauset (https://progeopik.cs.ut.ee/03_liitlaused.html), kirjuta eelnevalt kirjeldatud *bang-bang* kontroller eelnevalt avatud **praktikum3_bangbang.py** faili.

    Ülesanne on, et robot hoiaks end näiteks 0.5 meetri kaugusel takistusest.

4.  Kasuta väikeseid kiirusi (0.2 m/s või vähem).
5.  Salvesta fail, kasutades klahvikombinatsiooni Ctrl+X. 
6.  Koodi käitamiseks sisesta terminali

    **rosrun robotont_blank_scripts praktikum3_bangbang.py**

    Ctrl+C paneb programmi kinni.
7.  Demonstreeri töötavat kontrollerit juhendajale.

Vaatame, kuhu poole peaks sõitma kui ühes kohas asi ees on.
----------------------------------------------------------------
Selles ülesandes peab robot oskama nurga alt lähenedes avast läbi sõita.

1.  Ava terminal ja loo ssh-ühendus robotisse ja sisesta

    **roslaunch robotont_teleop teleop_with_laserscan.launch**

    VÕI
    kasuta eelmisest ülesandest juba käivat terminali.
    
2.  Võta ette uus terminal ning ava seal fail **praktikum3_betweenposts.py**
3.  Kasutades teadmisi ja oskusi eelnevast ülesandest, kirjuta koodis ettenähtud kohta oma kood. 
    Selle koodi abil peab robot oskama nurga alt avale lähenedes avast läbi sõitma. 
    Nüüd on kasutada ka vasaku ja parema sektori kaugused.
    Robot peab suutma avast läbi sõita mõlemal pildil näidatud juhul.

    .. figure:: ../images/lab03/yl2setup.png
            :scale: 70 %

            ..

4.  Koodi jooksutamiseks sisesta terminali

    **rosrun robotont_blank_scripts praktikum3_betweenposts.py**

5.  Demonstreeri töötavat robotit juhendajale.



.. include:: ../include/afterthelabrobot.rst