Praktikum 5 - 2d kaardistamine, automaatne navigeerimine
============================================================
.. .. include:: ../include/beforethelab.rst

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



.. .. include:: ../include/afterthelab.rst