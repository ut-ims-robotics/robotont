Praktikum 6 - 3D kaardistamine
====================================

3D kaardistamine
------------------

Kui eelnevalt oleme vaadanud vaid 2D andmeid, laserskanni ja kaugusi ning nende abil robotit liigutanud, 
siis nüüd hakkame kasutama 3D punktipilve, mille jäädvustamiseks meie kaamera võimeline on. 

Mis on punktipilv?
-------------------

Punktipilv näitab meile takistuste kaugusi kaamerast. Need kaugused saab kombineerida kaamerapildiga, et näha värvilist pilti. Proovime järele.

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Sisesta terminaliaknasse

    **roslaunch robotont_teleop teleop_bare_with_camera.launch**

3.  Ava uus terminaliaken ning trüki sinna
    
    **roslaunch robotont_description display_camera.launch**

4.  Nüüd peaksid nägema RVizis 3D kaamerapilti.

Proovime ka ringi sõita ja vaadata, kuidas robot maailma näeb.

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Trüki terminaliaknasse
    
    **roslaunch robotont_teleop teleop_pc_side.launch**
    
    Selles terminaliaknas saad robotit juhtida.

Kui oled lõpetanud, pane terminaliaknad kinni.

Kaardistamine töövahendiga RTAB-Map
---------------------------------------

Nagu 2D kaardiga, siis saame kaarti genereerida ka 3D vaates. 
Selline protsess on küll palju ressursinõudlikum, kuid saame oma kaardile juurde terve ruumimõõtme.

    .. figure:: ../images/lab06/3dmap.png
                :scale: 70 %

                ..

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Sisesta terminaliaknasse
    
    **roscore**
    
    See terminaliaken hoolitseb selle eest, et süsteem käimas püsiks, see terminaliaken võib jääda tahaplaanile käima.
3.  Ava terminaliaken ning loo ssh-ühendus robotisse.
4.  Sisesta käsureale

**roslaunch robotont_teleop teleop_3dmapping.launch**

5.  Ava uus terminaliaken ning trüki sinna
    
    **roslaunch robotont_description display_3dmapping.launch**

6.  Ava uus terminaliaken ning trüki sinna

    **roslaunch robotont_teleop teleop_pc_side.launch**

    Selles terminaliaknas saad robotit juhtida
7.  Sõida ringi ja kaardista ruumi.
8.  Kui oled oma kaardiga rahul, näita juhendajale.


Vaikeväärtustega on näha, et genereeritud kaart on võrdlemisi hõre: objekte ja nende asukohti on keeruline tuvastada, kuigi sügavuskaamera pilt ise on kvaliteetne. 
Seega proovime parandada seda olukorda, muutes mõningaid parameetreid.

*linear_update* - määrab kaardi uuendamiskiiruse lineaarse liikumise korral (mitme meetri järel kaarti uuendatakse)

*angular_update* - määrab kaardi uuendamiskiiruse pööramise korral (kui palju peab pöörama, et kaart uueneks)

*cell_size* - määrab punktide vahekauguse

1.  Võta ette terminaliaken, kus sisestasid
    
    **roslaunch robotont_teleop teleop_3dmapping.launch**

2.  Vajuta Ctrl+C, et lõpetada praegune protsess.
3.  Sisesta terminaliaknasse
    
    **roslaunch robotont_teleop teleop_3dmapping.launch angular_update:=0.1 linear_update:=0.1 cell_size:=0.1**

    Ctrl+C abil protsessi seisates, numbreid muutes ning siis uuesti käivitades, proovi aru saada, kuidas muutub genereeritav kaart.
4.  Muudatused parameetrites ja vaatlused, kuidas kaardi genereerimine muutub, pane kirja oma õpimappi.
5.  Korda protsessi kuni kaart on piisavalt selge, et sealt objekte eristada ning näita lõpptulemust juhendajale.

Proovime sõita ainult kaarti vaadates
--------------------------------------

Nüüd kui meil on olemas kvaliteetne kaart, siis proovime juhtida robotit vaadates ainult arvutiekraanil kaarti. 
Ülesanne on leida, mis on juhendaja öeldud kohtades. 
Sõita tuleb ettevaatlikult, sest robot ei pruugi reageerida nupuvajutustele kohe ning samuti ei pruugi pilt alati reaalajas uueneda. 

1.  Käivita eelnevalt paika sätitud argumentidega teleop_3dmapping.
2.  Sõiduta robot kõrvatuppa ning kaardista kogu ruum.
3.  Arvutiekraanilt nähtava kaardi abil selgita juhendajatele, mida võib leida sealt ruumist.
