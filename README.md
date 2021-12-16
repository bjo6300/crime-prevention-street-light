# 방범 가로등(crime prevention street light)

### 화재와 범죄를 예방한다.

## Built With
* Arduino Uno
* HC-06(Bluetooth module)
* bluetooth controler using smartphone <br> 
![image](https://user-images.githubusercontent.com/70627982/146410248-dd1a5820-29f3-4516-b9dd-abc517086a54.png)

## Pin Setting
* 2번 핀 : 블루투스
* 3번 핀 : 블루투스
* 4번 핀 : 스위치 버튼
* A0 : 조도센서
* A1 : 화재감지센서
* 8번 핀 : 수동부저
* 9번 핀 : 3색 LED - Red
* 10번 핀 : 3색 LED - Green
* 11번 핀 : 3색 LED - Blue


## Execute

### 낮
![image](https://user-images.githubusercontent.com/70627982/146411956-b4dbad60-34e5-459c-af28-218e8e241658.png) 
<br>
낮일 때 LED는 꺼져있다. (조도센서 및 3색 LED 이용) <br>
LCD는 시간과 가로등 ID가 5초마다 주기적으로 보여준다.<br>

### 밤
![image](https://user-images.githubusercontent.com/70627982/146412226-c0cf24d1-5fc6-4af8-8bf1-8e72937e7895.png)
<br>
밤이면 LED가 초록불로 켜진다. (조도센서 및 3색 LED 이용) <br>
LCD는 시간과 가로등 ID가 5초마다 주기적으로 보여준다. <br>

### 스위치를 누를 경우
![image](https://user-images.githubusercontent.com/70627982/146412627-3998beaf-afa7-4656-b267-03598c13971a.png)
<br>
사이렌 소리가 울리며 LED가 빨간색으로 변하고 깜빡인다. <br>
블루투스 모듈을 이용해 핸드폰으로 "SOS from (가로등 ID)"가 전송된다. <br>
LCD 내용이 "SOS!!!"로 변경된다. <br>
상황이 종료되면 다시 LED가 초록불로 바뀐다. <br>

### 화재 감지
![image](https://user-images.githubusercontent.com/70627982/146413016-da5a46ee-e113-44ab-a483-2e3e32acd3e3.png)
<br>
사이렌 소리가 울리며 LED가 빨간색으로 변하고 깜빡인다. <br>
블루투스 모듈을 이용해 핸드폰으로 "Fire from (가로등 ID)"가 전송된다. <br>
LCD 내용이 "Fire!!!"로 변경된다. <br>
상황이 종료되면 다시 LED가 초록불로 바뀐다. <br>

## License

Distributed under the APACHE 2.0 License. See `LICENSE` for more information.

## Contributor
* [bjo6300](https://github.com/bjo6300) <br>
* [zzih45](https://github.com/zzih45)

