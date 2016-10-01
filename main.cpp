#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <time.h>

std::mutex g_lock;

//g_lock.lock();
//std::this_thread::sleep_for(std::chrono::seconds(rand() % 5));
//g_lock.unlock();

std::vector<int> vec;
int				 numberElement = 0;
int countElement;
int countThread;
int countElementInVector;

void Multiplication()
{
	g_lock.lock();
	int _countCalculateElement = 0;

	for (numberElement; numberElement < vec.size(); ++numberElement)
	{
		vec[numberElement] *= rand() % 10 + 2;
		std::cout << numberElement << "  " << vec[numberElement] << " id: " << std::this_thread::get_id() << std::endl;

		if (++_countCalculateElement == countElementInVector)
		{
			++numberElement;
			break;
		}
	}

	g_lock.unlock();
}

int main()
{
	setlocale(LC_ALL, "russian");

	srand((unsigned int)time(0));
	
	int _countTask;
	std::cout << "Введіть номер завдання:";
	std::cin >> _countTask;

	int countThread = 0;

	switch (_countTask)
	{
		case 1:
		{
				  int _countElement;
				  std::cout << "Введіть кількість елементів: ";
				  std::cin >> _countElement;

				  int _temp = 0;
				  for (int i = 0; i < _countElement; i++)
				  {
					  _temp = rand() % 100 + 2;
					  vec.push_back(_temp);
				  }

			break;
		}
		case 2:
		{
				  countThread = 0;
				  std::cout << "Введіть кількість потоків: ";
				  std::cin >> countThread;

				  countElement = 0;
				  std::cout << "Введіть кількість елементів: ";
				  std::cin >> countElement;

				  int _tempValue = 0;
				  for (int i = 0; i < countElement; i++)
				  {
					  _tempValue = rand() % 100 + 2;
					  vec.push_back(_tempValue);
				  }

			break;
		}
		case 3:
		{
			
			break;
		}
	default:
		break;
	}

	time_t timer;
	struct tm y2k = { 0 };
	double seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(timer, mktime(&y2k));

	countElementInVector = vec.size() / countThread;

	std::vector<std::thread> _vecThread(countThread);
	for (int i = 0; i < countThread; i++)
	{
		_vecThread[i] = std::thread(Multiplication);
	}
		
	for (int i = 0; i < countThread; i++)
	{
		_vecThread[i].join();
	}

	double seconds2;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds2 = difftime(timer, mktime(&y2k));

	std::cout << seconds << " " << seconds2 << " : "<< seconds2 - seconds << std::endl;

	system("pause");
	return 0;
}

/*
	1. Реалізуйте послідовну обробку елементів вектора, наприклад, множення елементів вектора на число. Число елементів вектора задається параметром N.
	2. Реалізуйте багатопотокову обробку елементів вектора, використовуючи поділ вектора на рівне число елементів. Число потоків задається параметром M. (підказка: можна передбачити можливість розбиття діапазону 0..(N-1) на кілька, залежно від кількості потоків М. При запуску окремого потоку як аргумент передається або «індекс потоку», який визначає область масиву, який обробляється в даному потоці, або початковий і кінцевий індекси вхідного вектора).
	3. Виконайте аналіз ефективності багатопотокової обробки при різних параметрах N (10, 100, 1000, 100 000) і M (2, 3, 4, 5, 10). Результати подайте у табличній формі. (підказка: в якості ефективності роботи потоку можна вибрати час виконання потоком роботи).
*/