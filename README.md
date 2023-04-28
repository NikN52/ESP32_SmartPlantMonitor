# ESP32 SmartPlantMonitor

## Description (English)

SmartPlantMonitor is a project designed to automate plant care using the ESP32 microcontroller. The program collects data from various sensors, such as soil moisture, temperature and air humidity, and illumination. In addition, the system allows you to automatically control the watering and illumination of plants, depending on the read indicators. All data and component management is available through a web interface hosted on the ESP32 itself.

## Main functions

1. Data collection from sensors:
    - Soil moisture
    - Air temperature and humidity (DHT22)
    - Illumination (BH1750)

2. Management of system components:
    - Automatic watering of plants when soil moisture drops below a predetermined threshold
    - Automatic illumination of plants in low light conditions
    - Ability to turn on / off watering and lighting manually through a web browser

3. Wireless connection and data exchange:
    - Connecting ESP32 to WiFi
    - Sending data from sensors to a server or cloud storage (for example, ThingSpeak, Firebase or your own server) [optional]

4. Web server:
    - Displaying current data from sensors on the main page of the web server
    - Display simple graphs of soil moisture, air humidity, temperature and light on a separate page
    - Pump and backlight control via web browser via URL

## Code

The project is written in C++ using the Arduino IDE. The code consists of setting up and initializing components, functions for collecting data from sensors, managing components, and working with a web server. The web server uses simple HTML code and SVG graphics to display information and control components.

Important parts of the code:
- Functions for reading data from sensors
- Functions for pump and backlight control
- Functions for working with a web server, including route processors and generating HTML pages with graphs

## Setting up and using

To use SmartPlantMonitor, you must connect all sensors and components to the ESP32 in accordance with the code and connection diagram. Then upload the code to the microcontroller using the Arduino IDE, making sure all the necessary libraries are installed.

After downloading the code and connecting the ESP32 to the Wi-Fi network, the web interface will be available at the IP address of the microcontroller. The browser will open the main page, which will display the current values from the sensors, as well as links to control the pump, backlight and go to the page with graphs.

The graphs on the page are updated automatically every 5 seconds. Please note that these graphs are simple and only display the current sensor values. For more complex graphs and data history storage, it is recommended to use external servers or libraries.

## Conclusion

SmartPlantMonitor is a simple and effective plant care automation project using ESP32. It provides the ability to monitor and control the system through a web browser, and also offers basic graphs to visually display the current values of the sensors.

## Описание (Русский)

SmartPlantMonitor - это проект, предназначенный для автоматизации ухода за растениями с использованием микроконтроллера ESP32. Программа собирает данные с различных датчиков, таких как влажность почвы, температура и влажность воздуха, а также освещенность. Кроме того, система позволяет автоматически управлять поливом и подсветкой растений в зависимости от считанных показателей. Все данные и управление компонентами доступны через веб-интерфейс, размещенный на самом ESP32.

## Основные функции

1. Сбор данных с датчиков:
   - Влажность почвы
   - Температура и влажность воздуха (DHT22)
   - Освещенность (BH1750)

2. Управление компонентами системы:
   - Автоматический полив растений при снижении влажности почвы ниже заданного порога
   - Автоматическая подсветка растений при недостаточной освещенности
   - Возможность включать/выключать полив и подсветку вручную через веб-браузер

3. Беспроводное соединение и обмен данными:
   - Подключение ESP32 к Wi-Fi
   - Отправка данных с датчиков на сервер или облачное хранилище (например, ThingSpeak, Firebase или собственный сервер) [опционально]

4. Веб-сервер:
   - Отображение текущих данных с датчиков на главной странице веб-сервера
   - Отображение простых графиков влажности почвы, влажности воздуха, температуры и освещенности на отдельной странице
   - Управление насосом и подсветкой через веб-браузер с помощью URL

## Код

Проект написан на языке C++ с использованием Arduino IDE. Код состоит из настройки и инициализации компонентов, функций для сбора данных с датчиков, управления компонентами и работы с веб-сервером. Веб-сервер использует простой HTML-код и SVG-графики для отображения информации и управления компонентами.

Важные части кода:
- Функции для чтения данных с датчиков
- Функции для управления насосом и подсветкой
- Функции для работы с веб-сервером, включая обработчики маршрутов и генерацию HTML-страниц с графиками

## Настройка и использование

Для использования SmartPlantMonitor необходимо подключить все датчики и компоненты к ESP32 в соответствии с кодом и схемой подключения. Затем загрузите код в микроконтроллер с помощью Arduino IDE, убедившись, что все необходимые библиотеки установлены.

После загрузки кода и подключения ESP32 к сети Wi-Fi, веб-интерфейс будет доступен по IP-адресу микроконтроллера. В браузере откроется главная страница, на которой будут отображаться текущие значения с датчиков, а также ссылки для управления насосом, подсветкой и перехода на страницу с графиками.

Графики на странице обновляются автоматически каждые 5 секунд. Обратите внимание, что эти графики являются простыми и лишь отображают текущие значения датчиков. Для более сложных графиков и хранения истории данных рекомендуется использовать внешние серверы или библиотеки.

## Заключение

SmartPlantMonitor - это простой и эффективный проект для автоматизации ухода за растениями с использованием ESP32. Он предоставляет возможность мониторить и управлять системой через веб-браузер, а также предлагает базовые графики для наглядного отображения текущих значений датчиков.
