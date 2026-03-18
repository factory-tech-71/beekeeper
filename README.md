# Пчеловод — система управления роем БПЛА на C++ с поддержкой Hailo-ускорителя

**Пчеловод** — это open-source наземная станция управления (GCS) и система координации роя беспилотных летательных аппаратов (БПЛА), написанная на современном C++20 с использованием Qt6 и MAVSDK.  
Проект вдохновлён архитектурой Mission Planner, но переписан с нуля для лучшей производительности, поддержки аппаратного ускорения нейросетей (Hailo-8/8L/10) и удобной работы с роем.

## Основные возможности (на март 2026)

- Автоматическое обнаружение и подключение нескольких БПЛА по MAVLink (UDP/TCP/Serial)
- Управление отдельными аппаратами и роем целиком:
  - Arm / Disarm
  - Взлёт / Посадка
  - Переход в Offboard-режим и отправка setpoint’ов
- Простые построения роя в полёте (V-образный строй, возможность расширения)
- Загрузка одинаковой миссии на все аппараты из текстового файла
- Интеграция с **Hailo-ускорителем** (YOLOv8 и другие модели в формате .hef)
- Графический интерфейс на Qt6 + QML-карта (OpenStreetMap)
- Таблица состояния дронов + лог + кнопки быстрого управления

## Технологический стек

| Компонент              | Технология / Библиотека                  | Версия (рекомендуемая) |
|------------------------|-------------------------------------------|------------------------|
| Язык                   | C++                                       | 20                     |
| Сборка                 | CMake                                     | ≥ 3.20                 |
| GUI + Карта            | Qt6 (Widgets + Quick + Location)          | 6.5–6.7                |
| MAVLink / Управление   | MAVSDK (C++)                              | ≥ 2.0                  |
| Нейросети на краю      | HailoRT                                   | 4.18+                  |
| Модели                 | YOLOv8 (s/m/l) в формате Hailo .hef       | —                      |
| ОС (основные)          | Ubuntu 24.04 / 22.04, Raspberry Pi OS     | —                      |
| Зависимости            | OpenCV (опционально для обработки кадров) | 4.8+                   |

## Требования к оборудованию

Минимальные (для запуска GCS):

- Процессор: любой современный x86_64 / ARM64 (RPi 5)
- Оперативная память: ≥ 4 ГБ
- ОС: Linux (рекомендуется Ubuntu 24.04)

Рекомендуемые (для работы с Hailo + роем 5–10+ дронов):

- Hailo-8 / Hailo-8L / Hailo-10H на PCIe или M.2
- RPi 5 8 ГБ + Hailo-8L AI Kit
- или x86-компьютер + Hailo-8 PCIe-карта

## Установка и запуск

### 1. Зависимости (Ubuntu 24.04 / 22.04)

```bash
sudo apt update
sudo apt install -y \
    cmake build-essential git \
    qt6-base-dev qt6-declarative-dev qt6-location-dev qt6-positioning-dev \
    libopencv-dev libopencv-core-dev libopencv-imgproc-dev libopencv-videoio-dev
```
### 2. MAVSDK
```bash
wget https://hailo.ai/downloads/install-hailort.sh
chmod +x install-hailort.sh
sudo ./install-hailort.sh
```
### 3. HailoRT
Скачайте и установите последнюю версию HailoRT + PCIe-драйвер с официального сайта:
https://hailo.ai/developer-zone/software-downloads/
Или используйте скрипт установки (пример для RPi 5 + Hailo-8L):
```bash
wget https://hailo.ai/downloads/install-hailort.sh
chmod +x install-hailort.sh
sudo ./install-hailort.sh
```
### 4. Скачивание модели YOLOv8
```bash
mkdir -p models
cd models
wget https://hailo-model-zoo.s3.eu-west-2.amazonaws.com/ModelZoo/Compiled/v2.18.0/hailo8l/yolov8s_nms.hef -O yolov8s.hef
# или yolov8m.hef / yolov8l.hef — в зависимости от производительности
```
### 5. Сборка проекта
```bash
git clone https://github.com/factory-tech-71/beekeeper.git
cd beekeeper
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```
### 6. Запуск
```bash
./Pchelovod --connection udp://127.0.0.1:14550
```
### Быстрый старт с SITL (симулятор)
Запустите 3–5 экземпляров ArduCopter SITL:
```bash
sim_vehicle.py -v ArduCopter --console --map -I0 --out=udp:127.0.0.1:14550
sim_vehicle.py -v ArduCopter -I1 --out=udp:127.0.0.1:14551
sim_vehicle.py -v ArduCopter -I2 --out=udp:127.0.0.1:14552
```
В Пчеловоде подключитесь к первому порту (14550) — остальные дроны обнаружатся автоматически.
Дорожная карта (ближайшие планы на 2026)

 Полноценный динамический слой дронов на карте (Repeater + маркеры)
 Поддержка RTSP/GStreamer для получения видео с камер дронов
 Реальный Hailo post-processing с NMS и классами COCO
 Поддержка .plan файлов (QGroundControl) вместо простого txt
 Алгоритмы роевого интеллекта (formation control, obstacle avoidance)
 Поддержка PX4 + ArduPilot (сейчас лучше работает с ArduPilot)
 Многопоточная телеметрия и низкая задержка offboard

Лицензия
MIT License

