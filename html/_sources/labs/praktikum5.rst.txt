Praktikum 5 - 2d kaardistamine, automaatne navigeerimine
============================================================

Mis on kaardistamine?
-----------------------

Siiani oleme kasutanud vaid andmeid, mida me saame reaalajas. 
Aga kas poleks mitte tore, kui robotil oleks mälu? 
Kui sõidame mõnest takistusest mööda, siis on hea, kui jätame meelde, kus see takistus oli, et oskaks seda edaspidi vältida.
Selleks ongi kaardistamine. 
Käesolevas praktikumis kasutame kaugusanduri laserskanni, et luua ja jätta ka meelde kahemõõtmeline kaart roboti ümbrusest. 
Kaardi loomiseks ja sellel roboti asukoha määramiseks kasutame Google Cartographer on tarkvara, mida muuhulgas kasutavad ka Google’i isesõitvad autod.

Laseri visualiseerimine RVizis
---------------------------------

RViz on ROSis põhiline programm, mida kasutada erinevate andmete graafiliseks visualiseerimiseks. 
Kõigepealt kasutame RVizi roboti kaugusanduri laserskanni pidevaks kujutamiseks ning hiljem juba valminud kaarti nägemiseks.

1.  Ava uus terminal
2.  Loo *ssh*-ühendus robotisse
3.  Trüki terminali

    **roslaunch robotont_teleop teleop_with_laserscan.launch**

    See paneb käima roboti poolel vajaoleva tarkvara
4.  Ava uus terminal ning trüki sinna
    
    **roslaunch robotont_teleop teleop_pc_side.launch**
    
    Selles terminalis saad robotit juhtida.

5.  Ava veel üks terminal ning trüki sinna
    
    **roslaunch robotont_description display_laserscan.launch**

6.  Nüüd säti enda aknad nii, et näeksid korraga RVizi pilti ning seda terminali, kus klaviatuuriga juhtimine käib.
7.  Sõida ringi ja vaata, milline on pilt RVizis.
8.  Vaadates ainult RVizi, sõida läbi ruumi keskel oleva takistusraja.
9.  Kui oled valmis jätkma, sulge kõik terminaliaknad.

Proovime ruumi kaardistada
--------------------------------

Nüüd kui oleme näinud, mida robot näeb, on aeg kaardistama hakata.

1.  Ava terminal, loo ssh-ühendus robotisse ning trüki sinna
    
    **roslaunch robotont_teleop teleop_carto_with_navstack.launch**
    
    See tegeleb kaardistamisega.

2.  Nüüd ava uus arvutipoolne terminal ning trüki sinna

    **roslaunch robotont_description display_2dmapping.launch**

3.  Ava uus terminal ning trüki sinna
    
    **roslaunch robotont_teleop teleop_pc_side.launch**
    
    Selles terminalis saad robotit juhtida.

4.  Nüüd säti enda aknad nii, et näeksid korraga RVizi pilti ning seda terminali, kus klaviatuuriga juhtimine käib.
5.  Sõida robotiga seni ringi kuni kaart tundub selge ning oled sellega rahul.

Kui oled oma kaardiga rahul, näita juhendajale ning liigu järgmise punkti juurde.

Autonoomne liikumine
----------------------

Kui kaart on olemas, siis oskab robot ka enda asukoha seal leida. Veel enam, robot oskab ise sõita punktist A punkti B, mis talle ette anda.

1.  RVizi aknas kliki esimesena ikoonil “2D Pose Estimate” ning tiri nool roboti sõidusuunas 

    .. figure:: ../images/lab05/2dposeestimate.png
                :scale: 70 %

                ..

    .. figure:: ../images/lab05/poseestimatearrow.png
                :scale: 70 %

                ..

2.  Seejärel kliki sümbolil “2D Nav Goal” ning tiri nool kaardil sinna, kuhu tahad et robot sõidaks.

    .. figure:: ../images/lab05/2dnavgoal.png
                :scale: 70 %

                ..

    .. figure:: ../images/lab05/2dnavgoalarrow.png
                :scale: 70 %

                ..

Proovime ise 
--------------

Seda, kuidas robot navigeerimisel käitub, saame ka ise seadistada. 
Roboti liikumist kaardi abil kujundab valik parameetreid. 
Ülesandeks on suurendada ja vähendada nende parameetrite väärtusi ning jälgida roboti käitumist ja dokumenteerida, 
mida ja kuidas muutes roboti käitumine muutus.

Parameetrid on:

**acc_lim_x** - maksimaalne lineaarkiirendus

**acc_lim_theta** - maksimaalne nurkkiirendus

**yaw_goal_tolerance** - kui täpne on roboti suund lõpppunktis

**xy_goal_tolerance** - kui täpne on roboti asend lõpppunktis

Mis juhtub kui neid parameetreid suurendada või vähendada?

See juhend eeldab, et kaart on tehtud ja RViz käib.

1.  Loo ssh-ühendus robotisse
2.  Ava fail planner.yaml käsuga

    **nano ~/catkin_ws/src/robotont/robotont_teleop/config/planner.yaml**

3.  Muuda korraga ainult ühte eelnevaist  parameetrist oma äranägemise järgi.
4.  Salvesta ja välju. (Ctrl+X)
5.  Käivita uuesti planeerimistarkvara käsuga
    
    **roslaunch robotont_teleop navstack.launch**

6.  Proovi planeerida robotile teekond nagu eelmises ülesandes. 
    Kas robot käitus teisiti? 
    Kuidas robot käitus? 
    Kirjuta üles, mida muutsid ning kuidas roboti planeerimine selle peale muutus. 
    Olles terminalis, kus eelmist käsku jooksutasid, sule programm käsuga Ctrl+C. 
    Mine punkti 2 ja proovi parameetreid teisiti muuta. 

    .. figure:: ../images/lab05/tabel.png
                :scale: 70 %

                ..
