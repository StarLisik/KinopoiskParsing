using System;
using System.Net;
using System.Text;
using AngleSharp;
using AngleSharp.Dom;
using HtmlAgilityPack;
using System.Net.Http;
using static System.Formats.Asn1.AsnWriter;
using System.IO;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using AngleSharp.Io;
using AngleSharp.Io.Network;

namespace Parsing
{

    class Program
    {
        class Parsing
        {

            static async Task Main()
            {
                Console.OutputEncoding = Encoding.UTF8;

                List<string> places = new List<string>();
                List<string> names = new List<string>();
                List<string> times = new List<string>();
                List<string> directors = new List<string>();
                List<string> scores = new List<string>();
                List<string> numberOfMarks = new List<string>();
                List<string> proxyIp = new List<string>();
                List<string> proxyPort = new List<string>();
                string url = "";

                var lines = File.ReadAllLines(@"C:\MyFolder\VSProjects\Parsing\Test.txt");

                for (int i = 0; i < lines.Length; i++) // Adding proxies from file
                {
                    string ip = "";
                    string port = "";
                    string text = lines[i];

                    for (int t = 0; t < text.Length; t++)
                    {
                        if (text[t] == ' ')
                        {
                            for (int j = 0; j < t; j++)
                                ip += text[j];
                            proxyIp.Add(ip);
                            port = text.Remove(0, t + 1);
                            proxyPort.Add(port);
                        }
                    }

                }

                for (int i = 0; i < 20; i++) // Request for every page
                {
                    var proxy = new WebProxy
                    {
                        Address = new Uri($"http://{proxyIp[i % 3]}:{proxyPort[i % 3]}"), // rotate proxies every page
                        BypassProxyOnLocal = false,
                        UseDefaultCredentials = false,
                        Credentials = new NetworkCredential(
                            userName: "", // Enter login
                            password: "") // Enter password
                    };

                    var handler = new HttpClientHandler()
                    {
                        Proxy = proxy,
                    };

                    var client = new HttpClient(handler: handler, disposeHandler: true);
                    client.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.14; rv:68.0) Gecko/20100101 Firefox/68.0");

                    var config = Configuration.Default
                        .With(new HttpClientRequester(client))
                        .WithTemporaryCookies()
                        .WithDefaultLoader();
                    using var context = BrowsingContext.New(config);

                    if (i == 0)
                        url = "https://www.kinopoisk.ru/lists/movies/popular-films/";
                    else
                        url = $"https://www.kinopoisk.ru/lists/movies/popular-films/?page={i + 1}";

                    using var doc = await context.OpenAsync(url);

                    var title = doc.Title;

                    if (title == "Ой!")
                    {
                        Console.Write("Captcha has shown up! Abort mission!");
                        return;
                    }

                    var films = doc.GetElementsByClassName("styles_root__ti07r");

                    using (var writer = new StreamWriter(@"C:\MyFolder\VSProjects\Parsing\TestFilms.txt", true)) //Found information write down to file
                    {
                        foreach (var film in films)
                        {
                            places.Add(film.GetElementsByClassName("styles_position__TDe4E")[0].TextContent.Trim());
                            names.Add(film.GetElementsByClassName("styles_mainTitle__IFQyZ styles_activeMovieTittle__kJdJj")[0].TextContent.Trim());
                            times.Add(film.GetElementsByClassName("desktop-list-main-info_secondaryText__M_aus")[0].TextContent.Trim());
                            directors.Add(film.GetElementsByClassName("desktop-list-main-info_truncatedText__IMQRP")[0].TextContent.Trim());

                            if (film.GetElementsByClassName("styles_rating__LU3_x").Length == 0)
                            {
                                scores.Add("Оценок у фильма пока нет");
                                numberOfMarks.Add("0");
                            }
                            else if (film.GetElementsByClassName("styles_rating__LU3_x").Length == 1)
                            {
                                if (film.GetElementsByClassName("styles_kinopoiskValuePositive__vOb2E styles_kinopoiskValue__9qXjg").Length != 0)
                                {
                                    scores.Add(film.GetElementsByClassName("styles_kinopoiskValuePositive__vOb2E styles_kinopoiskValue__9qXjg")[0].TextContent.Trim());
                                    numberOfMarks.Add(film.GetElementsByClassName("styles_kinopoiskCount__2_VPQ")[0].TextContent.Trim());
                                }
                                else if (film.GetElementsByClassName("styles_kinopoiskValueNeutral__sW9QT styles_kinopoiskValue__9qXjg").Length != 0)
                                {
                                    scores.Add(film.GetElementsByClassName("styles_kinopoiskValueNeutral__sW9QT styles_kinopoiskValue__9qXjg")[0].TextContent.Trim());
                                    numberOfMarks.Add(film.GetElementsByClassName("styles_kinopoiskCount__2_VPQ")[0].TextContent.Trim());
                                }
                                else if (film.GetElementsByClassName("styles_kinopoiskValueNegative__Y75Rz styles_kinopoiskValue__9qXjg").Length != 0)
                                {
                                    scores.Add(film.GetElementsByClassName("styles_kinopoiskValueNegative__Y75Rz styles_kinopoiskValue__9qXjg")[0].TextContent.Trim());
                                    numberOfMarks.Add(film.GetElementsByClassName("styles_kinopoiskCount__2_VPQ")[0].TextContent.Trim());
                                }
                                else if (film.GetElementsByClassName("styles_empty__mT5M6").Length != 0)
                                {
                                    scores.Add("Оценок у фильма пока нет");
                                    numberOfMarks.Add("0");
                                }
                            }

                            writer.WriteLine("\nМесто в рейтинге: " + places.Last());
                            writer.WriteLine("Название: " + names.Last());
                            writer.WriteLine("Продолжительность: " + times.Last());
                            writer.WriteLine("Страна и режиссер: " + directors.Last());
                            writer.WriteLine("Рейтинг: " + scores.Last());
                            writer.WriteLine("Количество оценок: " + numberOfMarks.Last() + "\n");

                            Console.WriteLine("\nМесто в рейтинге: " + places.Last());
                            Console.WriteLine("Название: " + names.Last());
                            Console.WriteLine("Продолжительность: " + times.Last());
                            Console.WriteLine("Страна и режиссер: " + directors.Last());
                            Console.WriteLine("Рейтинг: " + scores.Last());
                            Console.WriteLine("Количество оценок: " + numberOfMarks.Last() + "\n");
                        }
                    }

                    Thread.Sleep(20000);
                }

                return;
            }
        }
    }
}