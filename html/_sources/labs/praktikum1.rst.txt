.. include:: ../include/special.rst

Praktikum 1 - Linux, ssh, roboti juhtimine klaviatuuriga
==========================================================

Kuidas kasutada Linuxit?
---------------------------
0.  Arvutisse sisselogimiseks kasuta parooli "t0ndik00bas”
1.  Ava linuxi terminali aken:

    a. Selleks vajuta vasakusse üles nurka -> Trüki sisse "terminal” -> ning vajuta Terminali ikoonil

        .. figure:: ../images/lab01/image1.png
            :scale: 70 %

            ..

        või vajuta klahvikombinatsiooni **Ctrl+Alt+T**

        Ilmub terminali aken:

        .. figure:: ../images/lab01/image2.png
            :scale: 70 %

            ..

2. **ls**

    Käsk **ls** ehk *list* näitab, mis on selles kaustas, kus parasjagu asud.

    a. 

        .. figure:: ../images/lab01/image3.png
            :scale: 70 %

            ..
            
        Trüki terminali **ls** ning vaata väljundit. Need on kaustad ja failid, mis asuvad selles kaustas, kus praegu asud. 
        *Mis värvi on väljundis kaustad ja mis värvi on failid?*

    b.  Trüki terminali **ls -a**. Nüüd ilmub väljundisse palju rohkem nimesid.
        Punktiga algavad kasutad ning failid on Linuxis enamasti peidetud. Nendes kaustades ning failides asuvad tavaliselt konfiguratsioonid operatsioonisüsteemile ning programmidele, 
        seega ei tohi neid ilma Linuxist sügavamaid teadmisi omamata muuta.
        
        .. figure:: ../images/lab01/image4.png
            :scale: 70 %

            ..

    c.  Trüki terminali **ls -la**. *Mis muutus? Mida uut väljundis failide kohta näed?*
        
        .. figure:: ../images/lab01/image5.png
            :scale: 70 %

            ..
        

        .. figure:: ../images/lab01/image6.png
            :scale: 70 %

            ..

3. **mkdir**

    Nüüd õpime, kuidas teha Linuxi terminalis kausta.

    a.  Teeme kausta nimega "asjad”. Linuxis kausta tegemiseks on käsk **mkdir** ehk *make directory*. Trüki terminali **mkdir asjad**. 

        .. figure:: ../images/lab01/image7.png
            :scale: 70 %

            ..

    b.  Nüüd kasuta eelmises punktis *list*'i kohta õpitut, et näha, kas sinu tehtud kaust tekkis sinna.  Linuxis pääsed eelmiste käskude ligi ka kasutades üles noolt.

        .. figure:: ../images/lab01/image8.png
            :scale: 70 %

            ..

4. **cd**  

    Selleks, et terminalis kaustade vahel liikuda, on käsk **cd** ehk *change directory*.
    
    a.  Lähme kausta, mis me just tegime. Selleks kirjutame terminalis **cd asjad**.

        .. figure:: ../images/lab01/image9.png
            :scale: 70 %

            ..

    b.  Nüüd kasuta käsku **ls**, et näha, kas kaust on tühi.

        .. figure:: ../images/lab01/image10.png
            :scale: 70 %

            ..

    c.  Teeme siia kausta ühe alamkausta nimega "asi”. Selleks kirjutame **mkdir asi**.
    d.  Trüki terminali **ls -a**. Siin näed kolme kausta. ".”, "..” ja "asi”. 

        .. figure:: ../images/lab01/image11.png
            :scale: 70 %

            ..

    e.  Linuxis kaust ".” tähendab seda kausta, kus praegu asud. Kaust "..” tähendab praeguse kausta ülemkausta.
    f.  Lähme tehtud alamkausta, kasutades käsku **cd asi**. Selleks, et tagasi, kaust ülespoole, saada, kasutame käsku **cd ..**.

        .. figure:: ../images/lab01/image12.png
            :scale: 70 %

            ..

5.  **pwd** ja failisüsteem

    Käsk **pwd** näitab täielikku teed failisüsteemis praegusesse kausta.

    .. figure:: ../images/lab01/image13.png
            :scale: 70 %

            ..

    a.  Kirjuta terminali **cd**, et saada kodukausta. (Kui käsule **cd** ei anta argumente, siis viib see käsk kodukausta)

        .. figure:: ../images/lab01/image14.png
            :scale: 70 %

            ..

    b.  Selleks, et näha mingi kausta sisu, saab samuti kasutada käsku **ls**. Kirjuta terminali **ls asjad**. Nii näed kausta "asjad” sisu.
    c.  Nüüd kirjuta terminali **ls asi**. *Mis nüüd juhtus?*

        .. figure:: ../images/lab01/image15.png
            :scale: 70 %

            ..

    d.  Selleks, et näha kodukaustast kausta "asi” sisu, tuleb käsule ls anda tee selle kaustani. Antud juhul on selleks "asjad/asi”. Seega kausta "asi” sisu näeme, kui trükime kodukaustas "ls asjad/asi”. Hetkel on see kaust tühi.

        .. figure:: ../images/lab01/image16.png
            :scale: 70 %

            ..

6. **nano**
    a.  Kasuta käsku **cd**, et minna kausta "asi”.

        .. figure:: ../images/lab01/image17.png
            :scale: 70 %

            ..

    b.  Selles kaustas tee uus tekstifail, kasutades tekstiredaktorit **nano**. Selleks, et teha fail nimega "test.txt” ja sinna midagi kirjutada, kasutame kaustas "asi” käsku **nano test.txt**.

        .. figure:: ../images/lab01/image18.png
            :scale: 70 %

            ..

        Nüüd avanes järgnev pilt:

        .. figure:: ../images/lab01/image19.png
            :scale: 70 %

            ..

    c.  Olles **nano**'s, saad kirjutada selle faili sisse, mis just avasid. Kirjuta midagi siia. 

        .. figure:: ../images/lab01/image20.png
            :scale: 70 %

            ..

        Selleks, et nanost väljuda, vajutame alguses Ctrl+X. Seejärel küsib programm, kas soovid faili salvestada. Trüki sisse "y” ning vajuta Enterit.

        .. figure:: ../images/lab01/image21.png
            :scale: 70 %

            ..

        .. figure:: ../images/lab01/image22.png
            :scale: 70 %

            ..

    d.  Kontrolli, et fail tekkis, kasutades käsku **ls**.

        .. figure:: ../images/lab01/image23.png
            :scale: 70 %

            ..
           
7. **cat**
    a.  Käsk **cat** võimaldab näha tekstifailide sisu ilma faili avamata. Olles kaustas "asi”, trüki terminali **cat test.txt**. *Kas ilmus tuttav tekst?*

        .. figure:: ../images/lab01/image24.png
            :scale: 70 %

            ..
            
    b.  Lähme ühe kausta ülespoole, kasutades käsku **cd ..**. Käsuga **cat**, nagu eelnevalt käsuga **ls** (ja enamasti Linuxi käskudega),
        saab anda ette tee failisüsteemis ehk saame vaadata faili sisu, mis ei asu samas kaustas, kus meie. 
        Olles kaustas "asjad”, trüki terminali **cat asi/test.txt**. *Kas ilmus sama tekst?*

        .. figure:: ../images/lab01/image25.png
            :scale: 70 %

            ..

    c.  Kasuta nüüd eelnevaid teadmisi, et muuta test.txt sisu ning kuva see ekraanile kasutades käsku **cat**.

        .. figure:: ../images/lab01/image26.png
            :scale: 70 %

            ..

8.  **mv** ja **cp** ja **rm**

    Käsku **mv** ehk move saame kasutada, et faile liigutada ja ümber nimetada.
    Käsku **cp** ehk copy saame kasutada, et faile kopeerida.
    Käsku **rm** ehk remove saame kasutada, et faile kustutada.

    a.  Kasutame käsku **cp**, et kopeerida "test.txt” üks kaust kõrgemale. Selleks lähme kausta "asjad” ning kasutame käsku **cp asi/test.txt .** 
        
        Siin näeme ka punkti kasutust käsus, mis tähendab praegust kausta.
        **cp** ja **mv** tahavad kahte argumenti, esimesena fail, mida liigutatakse ja teiseks asukoht, kuhu liigutatakse.
    b.  Kontrolli käsuga **ls**, kas mõlemas kaustas on nüüd fail "test.txt”.
  
        .. figure:: ../images/lab01/image27.png
            :scale: 70 %

            ..

    c.  Järgmisena kasutame käsku **rm**, et kustutada ära originaalfail. Olles kaustas "asjad”, trüki sisse **rm asi/test.txt**.
    d.  Kontrolli, kas nüüd on "test.txt” ainult ühes kaustas.

        .. figure:: ../images/lab01/image28.png
            :scale: 70 %

            ..

    e.  Selleks, et faile ümber nimetada ja kaustast kausta tõsta, kasutame käsku **mv**. 
        Tõstame faili "test.txt” kausta "asi” ning nimetame selle ümber failiks "test1.txt”. 
        Selleks, olles kaustas "asjad”, trüki terminali **mv test.txt asi/test1.txt**.
    f.  Kontrolli, kas sai fail ilusti liigutatud ja nimetatud. Nüüd ei tohi enam faili "test.txt” eksisteerida.

        .. figure:: ../images/lab01/image29.png
            :scale: 70 %

            ..

.. Kui töötad simulatsioonis
.. -------------------------------------

.. .. toggle-header::
..     :header: **Kui töötad simulatsioonis**

..         Kui töötad simulatsioonis, siis järgnevate peatükkide asemel lähevad käiku teised käsud.
..         Antud juhul saab kogu simulatsiooni ning klaviatuuriga juhtimise käima panna ühe käsuga.

..         1.  Ava terminal.
..         2.  Sisesta käsk
..             **roslaunch robotont_description gazebo_teleop_keyboard.launch**
..         3.  Kui kõik läks hästi, siis avanes simulatsioon, kus näed robotit.
..         4.  Juhendi lõpust leiad, mis nuppudega robotit juhtida. Juhtimiseks peab olema terminaliaken aktiivne.

Kaugteel robotisse sisenemine (ssh)
-------------------------------------

1.  Ava Linuxi terminali aken.
2.  Trüki sinna: **ssh kasutaja@clearbot-*** ja vajuta ENTER.
    NB! Tärni asemel sisesta oma roboti number, näiteks **ssh kasutaja@clearbot-2**.

    .. figure:: ../images/lab01/image30.png
        :scale: 70 %

        ..

    a. Kui arvuti küsib yes/no variante, trüki sisse "yes” ning vajuta enter.
3.  Järgmisena küsitakse parooli. 
    :red:`NB! Linuxi terminali aknas ei ole parooli trükkimist näha. Seega, ära ehmu, kui sisestamisel tärne või mumme ei ilmu.  Lihtsalt sisesta parool ja vajuta Enter.`
    
    a.  Parool on: t0ndik00bas
    b.  Kui tegid parooli sisestamisel vea, ilmub selline teade ja saad veel kaks korda uuesti proovida:

        .. figure:: ../images/lab01/image31.png
            :scale: 70 %

            ..

4.  Kui parool oli õige, siis ilmub järgmine tervitus ning oled saanud ligipääsu oma robotile:

    .. figure:: ../images/lab01/image32.png
        :scale: 70 %

        ..

    **Nüüdsest on see terminali aken ühenduses robotiga ja saame seal erinevaid programme käivitada.**

    :red:`NB! Kuigi terminaliaken on avatud sülearvutis, siis tegelikult jooksutatakse siin sisestatud käske hoopis roboti peal, kus on samuti paigaldatud Ubuntu Linux. 
    Seda on näha sellest, et rohelises kirjas olev arvutinimi on muutunud roboti nimeks.`

Roboti ROS juhtprogrammi käivitamine
-------------------------------------

Alustuseks käivitame arvuti peal ROS-i programmi, mis korraldab arvuti ja ülejäänud roboti elektroonika vahelist suhtlust.
Selleks kirjutame samas (kasutaja@clearbot-\*) terminali aknas:

**roslaunch robotont_teleop teleop_bare.launch**

    .. figure:: ../images/lab01/image33.png
        :scale: 70 %

        ..

**Nüüd sinu robot töötab ning ootab juhiseid.**

Roboti juhtimine klaviatuuriga
-------------------------------------
Korrektselt vormistatud liikumisjuhiste andmiseks kasutame programmi, mis võimaldab meil robotit arvutiklaviatuuri abil juhtida.

1.  Avame uue terminali akna.

    Nüüd on sul sülearvutis lahti vähemalt kaks terminaliakent, millest üks on otseühenduses robotiga. Kas saad aru, kumb on kumb?

2.  Käivitame äsja avatud terminaliaknas, mis käivitab programme sülearvutis, ROS sõlme, mis jälgib terminali aknas klahvivajutusi. 
    See sõlm saadab klahvivajutused edasi robotile arusaadaval kujul. Sõlme käivitamiseks sisesta terminali järgmine käsk ja vajuta Enter klahvi:

 
    **roslaunch robotont_teleop teleop_pc_side.launch**

3.  Tulemus peaks olema selline:

    .. figure:: ../images/lab01/image34.png
        :scale: 70 %

        ..

    :red:`NB! Sellest hetkest saab klahvivajutustega panna robotit eri suundades sõitma. Selleks, et klahvivajutused mõjuks, peab see terminaliaken olema aktiivne.
    ROBOTI PEATAMISEKS VAJUTA "k" KLAHVI!
    Kui kaotad roboti üle kontrolli, siis tõsta lihtsalt robot õhku ja kutsu juhendaja!`

**Sõitmiseks:**

    .. figure:: ../images/lab01/image35.png
        :scale: 70 %

        ..

Selleks, et programme Linuxi terminalis kinni panna, on klahvikombinatsioon Ctrl+C.
