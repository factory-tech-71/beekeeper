#!/usr/bin/env bash

echo "Запуск 3 дронов ArduCopter SITL..."

sim_vehicle.py -v ArduCopter --console --map -I0 --out=udp:127.0.0.1:14550 --model + &
sleep 3

sim_vehicle.py -v ArduCopter -I1 --out=udp:127.0.0.1:14551 --model + &
sleep 3

sim_vehicle.py -v ArduCopter -I2 --out=udp:127.0.0.1:14552 --model + &

echo "SITL запущен. Подключайся в Пчеловоде к udp://:14550"
echo "Для остановки: pkill -f sim_vehicle.py"