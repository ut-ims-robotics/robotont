Enne praktikumi juurde asumist
--------------------------------------

1.  Mine lehele https://github.com/**sinu kasutajanimi**/robotont_blank_scripts, kus asenda **sinu kasutajanimi** oma kasutajanimega. 
2.  Vajuta rohelist nuppu “Clone or download”
3.  Kopeeri sealt aadress
4.  Ava terminal, **loo ssh-ühendus robotisse** ning trüki sinna

    **cd catkin_ws/src**

5.  Seejärel sisesta

    **git clone -sinu-kopeeritud-link-**

6.  Seejärel sisesta

    **cd robotont_blank_scripts**

7.  Seejärel

    **git config user.email "YOUR-EMAIL-HERE"**

8.  Seejärel

    **git config user.name "YOUR-NAME-HERE"**

9.  Seejärel sisesta

    **git pull https://github.com/ut-ims-robotics/robotont_blank_scripts.git**


10. Nüüd trüki terminali

    **catkin build**

11. Kui see protsess on lõpetanud edukalt, sulge terminal ja oled valmis praktikumiga jätkama.


