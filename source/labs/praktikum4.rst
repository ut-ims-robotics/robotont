Praktikum 4 - AR markerid
====================================
.. include:: ../include/beforethelabrobot.rst

Mis on liitreaalsus (AR) ja AR-markerid?
---------------------------------------------

Paljud on kuulnud virtuaalreaalsusest (VR), 
kus kogu maailm on genereeritud arvuti poolt ning kasutajal on võimalus selles maailmas olla ja 
sellega interakteeruda. 
Liitreaalsus ehk lühidalt AR (ingl *augmented reality*) ühendab päris maailma ja virtuaalmaailma. 
AR’is on seotud päris maailma pildiga virtuaalsed objektid, näiteks uuematele telefonidele on äpid, 
kus filmid näiteks lauda ja selle laua peal hakkab telefoniekraanil mingi mehike tantsima.
Sellist sidusust saab ka praktilistel eesmärkidel ära kasutada. 
Näiteks arstina saad uurida interaktiivselt patsiendi sisemust ilma teda lahti lõikamata.

.. figure:: ../images/lab04/futu.png
            :scale: 70 %

            ..

AR-markerid on spetsiaalselt disainitud kujundid, 
mille võid näiteks välja printida ja kuskile kleepida ja arvuti tunneb kaamera abil ära selle markeri asukoha, 
suuna ning markeri numbri. 
Nende markerite kasutamine aitab arvutil paremini aru saada, kuidas ja kus pärismaailmas asjad on ja näiteks, 
et kuhu infot visualiseerida.
Meie kasutame AR-markereid, et aidata robotil aru saada, kuhu peaks liikuma.

.. figure:: ../images/lab04/tags.png
            :scale: 70 %

            ..

Siin pildil on AR-markerid 0-8.

Tuvastame markeri ja visualiseerime seda RVizis
---------------------------------------------------

Esmalt vaatame, kuidas robot markerit näeb.

1.  Selleks ava terminal ning loo ssh-ühendus robotisse.
2.  Uues terminalis sisesta 

    **roslaunch robotont_training robotont_ar.launch**

    See paneb käima ROSi draiveri, mis kontrollib rataste kiirusi vastavalt meie sõnumitele 
    ning tunneb kaamera abil ära ning publitseerib AR-markerite asukoha. 
    **Seda terminali ära kinni pane!**

3.  Ava uus terminal ning trüki sinna

    **roslaunch robotont_description display_ar_marker.launch**

4.  Nüüd võta AR-marker kätte ning liiguta seda kaamera ees, peaksid nägema RVizis, et ilmub roboti ette marker. 
    Võid proovida ka mitut markerit korraga. 
    Kui ei ilmu, kutsu juhendaja.


Kuidas töötab koordinaatteljestik
------------------------------------

3D-teljestikus on kolm telge, mida nimetame *x*, *y* ja *z*. 
Pöörded ümber nende telgede on vastavalt *roll*, *pitch* ja *yaw*. 
Demonstreerime neid, kasutades inimpead. 
Edasi-tagasi liikumine on x-teljel, vasakule-paremale liikumine on y-telg ja üles-alla liikumine on z-telg. 
Sellele vastavalt on *roll* pea kallutamine küljelt-küljele, 
*pitch* on pea noogutamine üles-alla ja *yaw* on pea pööramine vasakule-paremale.

.. figure:: ../images/lab04/robotontaxes.png
            :scale: 70 %

            ..

Samuti kui me hoiame seda AR-markerit kaamera ees, siis kaugus kaamerast otse on x-telg ja seda, 
kui palju marker on kaamera keskelt kõrvale kaldunud, 
näitab y-telg. *roll*, *pitch* ja *yaw* ehk RPY sõltuvad sellest, kuidas markerit käes hoida.

Ülesanne 0
-------------

Vaatame, mida näeb robot arvudena AR-markeri kohta.

1.  Ava uus terminal, loo ssh-ühendus robotisse ning trüki sinna 

    **rosrun robotont_blank_scripts praktikum4_ar.py**

2.  Nüüd kui paned AR-markeri kaamera ette (nii, et käega osa sellest ära ei kata), 
    siis peaksid terminalist nägema kus see marker kaamera suhtes asub. 
    Samuti saad teada, mis on markeri ID, seda pead hiljem ka kasutama.
    Terminalis prinditakse välja "Marker ID"; mis on markeri number, "Marker: X Y Z", 
    mis on markeri koordinaadid kaamera suhtes, "Direction from camera", 
    mis näitab, mis suunas marker on kaamera suhtes ja "RPY", mis on järjestikku 
    *roll*, *pitch* ja *yaw* väärtused.

Ülesanne 1
-------------

Tee programm, mis liigub edasi-tagasi vastavalt AR-markeri kaugusele.

1.  Ava uus terminal, loo ssh-ühendus ning seal ava praktikum4_ar.py fail, kasutades käsku

    **nano catkin_ws/src/robotont_blank_scripts/scripts/praktikum4_ar.py**

2.  Otsi koodis kommentaar "CHANGE THIS NUMBER TO YOUR MARKER ID" 
    ja selle rea all muuda *marker.id* == väärtus end markerile vastavaks.
3.  Implementeeri funktsioon, mis liigub olenevalt AR-markeri kaugusest edasi või tagasi. 
    Robot peab proovima hoida AR-markeri endast alati 0.5 meetri kaugusel.
    Selleks on sul ette tehtud funktsioon nimega *keep_distance*. 
    Funktsiooni argumentideks on markeri asukoht kaamera suhtes (*x*, *y*, *z*, *roll*, *pitch*, *yaw*) 
    ja roboti liikumissõnum *twist*, mida saad kasutada analoogselt *vel_msg* muutujaga 2. praktikumis. 
    Funktsioon peabki tagastama *twist* muutuja, ehk siis käsk, kuidas peab robot liikuma. 
    Eeskujuks võid võtta 3.praktikumis tehtud *bang-bang* kontrolleri.


4.  Skriptist väljumiseks Ctrl+X, salvesta ja skripti saad jooksutada käsuga

    **rosrun robotont_blank_scripts praktikum4_ar.py**

    Ctrl+C, et skript peatada.
5.  Demonstreeri töötavat kontrollerit juhendajale.

Ülesanne 2
-------------

Tee programm, mis liigub küljelt-küljele vastavalt AR-markeri asukohale

1.  Ava **praktikum4_ar.py** fail.
2.  Implementeeri funktsioon, mis liigub olenevalt AR-markeri y-koordinaadist küljelt küljele. 
    Robot peab proovima hoida AR-markeri enda jaoks keskel.
    Selleks on koodis valmis pandud funktsioon *keep_center*.
    NB! Samaaegselt töötab ka eelmises ülesandes tehtud funktsioon.
3.  Demonstreeri töötavat kontrollerit juhendajale.

Ülesanne 3
-------------
Tee programm, mis pöörab vastavalt AR-markeri suunale mis pöörab nii, et AR-marker oleks otse vastas.

1.  Ava **praktikum4_ar.py** fail.
2.  Seal on valmis pandud funktsioon nimega *turn_towards_ar*
3.  Implementeeri funktsioon, mis pöörab AR-markeri poole. Eesmärk on, et kui AR-markerit pöörata, siis robot keerab nii, et marker oleks täpselt roboti vastas. Vihje: Jälgi mis väärtus markerit pöörates muutub, et teada, mille järgi robotit kontrollida.
4.  Demonstreeri töötavat kontrollerit juhendajale.

BOONUS: Ülesanne 4
------------------
Tee programm, mis teeb ühe markeriga üht asja, teisega teist. Näiteks kui robotile näidata markerit number 3, teeb robot enda ümber tiiru, kui näidata markerit number 4, proovib robot hoida markerit poole meetri kaugusel nagu esimeses ülesandes.

1.  Ava praktikum4_ar_tricks.py fail, kasutades käsku

    **nano catkin_ws/src/robotont_blank_scripts/scripts/praktikum4_ar_tricks.py**

2.  Kirjuta koodis märgitud alasse oma kood, millega robot teeb ühe markeri puhul üht trikki, teise markeriga teist trikki.
3.  Demonstreeri töötavat koodi juhendajale.





.. include:: ../include/afterthelabrobot.rst