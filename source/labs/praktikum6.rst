Praktikum 6
====================================

3D kaardistamine
------------------

Kui eelnevalt oleme vaadanud vaid 2D andmeid, laserskanni ja kaugusi ning nende abil robotit liigutanud, 
siis nüüd hakkame kasutama 3D punktipilve, mille jäädvustamiseks meie kaamera võimeline on. 

Mis on punktipilv?
-------------------

Punktipilv näitab meile takistuste kaugusi kaamerast. Need kaugused saab kombineerida kaamerapildiga, et näha värvilist pilti. Proovime järele.

1.  Ava terminal ning loo ssh-ühendus robotisse.
2.  Sisesta terminali

    **roslaunch robotont_teleop teleop_bare_with_camera.launch**

3.  Ava uus terminaliaken ning trüki sinna
    
    **roslaunch robotont_description display_camera.launch**

4.  Nüüd peaksid nägema RVizis 3D kaamerapilti.

Proovime ka ringi sõita ja vaadata, kuidas robot maailma näeb.

1.  Ava terminaliaken ning loo ssh-ühendus robotisse.
2.  Trüki terminali
    
    **roslaunch robotont_teleop teleop_pc_side.launch**
    
    Selles terminalis saad robotit juhtida.

Kui oled lõpetanud, pane terminalid kinni.

Rtabmapiga kaardistamine
--------------------------

Nagu 2D kaardiga, siis saame kaarti genereerida ka 3D vaates. 
Selline protsess on küll palju ressursinõudlikum, kuid saame juurde terve dimensiooni oma kaardile.

    .. figure:: ../images/lab06/3dmap.png
                :scale: 70 %

                ..

1.  Ava terminal ning loo ssh-ühendus robotisse.
2.  Sisesta terminali
    
    **roscore**
    
    See terminal hoolitseb selle eest, et süsteem käimas püsiks, see terminal võib jääda tahaplaanile käima.
3.  Ava terminal ning loo ssh-ühendus robotisse.
4.  Sisesta terminali

**roslaunch robotont_teleop teleop_3dmapping.launch**

5.  Ava uus terminal ning trüki sinna
    
    **roslaunch robotont_description display_3dmapping.launch**

6.  Ava uus terminal ning trüki sinna

    **roslaunch robotont_teleop teleop_pc_side.launch**

    Selles terminalis saad robotit juhtida
7.  Sõida ringi ja kaardista ruumi.
8.  Kui oled oma kaardiga rahul, näita juhendajale.


Vaikeväärtustega on näha, et kaart on hõre ja raske on aru saada, mis kus on, kuigi sügavuskaamera näitab ilusat pilti. 
Seega proovime parandada seda olukorda, muutes mõningaid parameetreid.

*linear_update* - määrab kaardi uuendamiskiiruse lineaarse liikumise korral

*angular_update* - määrab kaardi uuendamiskiiruse pööramise korral

*cell_size* - määrab punktide vahekauguse

1.  Võta ette terminal, kus sisestasid
    
    **roslaunch robotont_teleop teleop_3dmapping.launch**

2.  Vajuta Ctrl+C, et lõpetada praegune protsess.
3.  Sisesta terminali
    
    **roslaunch robotont_teleop teleop_3dmapping.launch angular_update:=0.1 linear_update:=0.1 cell_size:=0.1**

    Siin proovi numbreid muuta ja vaata kuidas muutub kaardi genereerimine.
4.  Muudatused parameetrides ja vaatlused, kuidas kaardi genereerimine muutub, pane kirja õpimappi.
5.  Korda protsessi kuni kaart on piisavalt selge, et sealt objekte eristada ning näita juhendajale.

Proovime sõita ainult kaarti vaadates
--------------------------------------

Nüüd kui meil on olemas kaart, siis proovime sõita niimoodi, et vaatame ainult kaarti. 
Ülesanne on leida, mis on juhendaja öeldud kohtades. 
Sõita tuleb ettevaatlikult, sest robot ei pruugi reageerida nupuvajutustele kohe ning samuti ei pruugi pilt alati reaalajas uueneda. 

1.  Käivita eelnevalt paika sätitud argumentidega teleop_3dmapping.
2.  Mine kõrvaltuppa ning kaardista kogu tuba.
3.  Vaadates arvutist kaarti, näita juhendajale, mis on postide taga.
