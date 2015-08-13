**Сценарий для тестового приложения**

* создаётся основной поток, он создаёт ещё 3 потока;
* первый и второй при получении сообщения "старт" от основного
* начинают читать каждый из текстового файла, указанного в
* сообщении, по одной строке и отдавать сообщением в основной поток;
* основной поток при получении сообщения, содержащего строку из файла, отдаёт её в третий поток сообщением;
* третий поток при получении сообщения, содержащего строку, записывает её в другой файл;
* когда поток прочитал весь файл он сообщает об этом в основной;
* когда оба потока закончили чтение, основной поток отправляет сообщение о завершении в каждый поток;
* основной поток завершается после завершения всех дочерних потоков;

**Требования к тестовому приложению**

* сделать консольное приложение для проверки работоспособности выполненой задачи;
* основной поток не является точкой входа приложения;
* должно быть хотя бы три типа сообщений;
* сообщение об ошибке должно содеражть текст и код ошибки;
* при получении сообщения об ошибке от дочернего потока, основной поток отправляет сообщение о завершении в каждый поток;
* дочерние потоки работают до получения сообщения о закрытии от основного потока;
* дочерние потоки работают с разной скоростью (искусственной задержкой) между проверкой и обработкой сообщений:
``
первый 200мс;
второй 300мс;
третий 100мс;
``
