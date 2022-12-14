# Parsing
Курсовая работа по сбору и анализу данных с Сайта Кинопоиск

В папке Kinopoisk находится код для сбора данных.

Для запуска приложения нужно открыть файл /bin/Debug/net6.0/Parsing.exe.
Собранные данные сохраняются в файл TestFilms.txt в той же папке, что и приложение.

Для того, чтобы использовать прокси во избежания капчи, в файле Proxies.txt нужно указать используемые прокси в формате (данные вводятся через пробел): ip port username password
Например: 12.34.56.78 8080 user pass

В папке Analyzer программа для анализа полученных данных.
Запускается файлом Analyzer.exe

![Скриншот 13-12-2022 142822](https://user-images.githubusercontent.com/39351000/207306959-157dc7ee-0178-465d-bf19-2c09a221f03c.jpg)

Реализована выборка по параметрам: год, страна, жанр, год и страна, год и жанр, страна и жанр. Также реализована сортировка по типу данных. Результат анализа предварительно выводится пользователю для просмотра.

![image](https://user-images.githubusercontent.com/39351000/207307023-be89eb98-aec9-466b-af7a-89d05e20c1c9.png)

Данные для дальнейшего использования сохраняются в Excel.
