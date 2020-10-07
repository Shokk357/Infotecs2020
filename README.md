# Infotecs2020

Тестовое задание для стажировки.

Задание состоит из двух программ, которые необходимо реализовать. Взаимодействие программ должно быть реализовано через использование сокетов.

##Программа  №1. 
Должна состоять из двух потоков и одного общего буфера.

Поток 1. Принимает строку, которую введет  пользователь. Должна быть проверка, что строка состоит только из цифр и не превышает 64 символа. 
После проверки строка должна быть  отсортирована по убыванию и все четные элементы заменены на латинские буквы «КВ». 
После данная строка помещается  в общий буфер и поток должен ожидать дальнейшего ввода пользователя.

Поток 2. Должен  обрабатывать  данные которые помещаются в общий буфер. После получения данных общий буфер затирается. 
Поток должен вывести полученные данные на экран, рассчитать  общую  сумму всех  элементов , которые являются численными значениями. 
Полученную сумму передать в Программу №2. После этого поток ожидает следующие данные.

##Программа №2. 
Ожидает данные от  Программы №1. 

При получении  данных происходит анализ из скольки символов состоит переданное значение. 
Если оно больше 2-ух символов и если оно кратно 32 выводит сообщение о полученных данных, иначе выводится сообщение об ошибке. 
Далее программа продолжает ожидать данные.