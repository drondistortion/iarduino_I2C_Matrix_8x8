//	Библиотека для работы со светодиодной матрицей 8x8: http://iarduino.ru/shop/Expansion-payments/led-matrica-8x8---i2c-trema-modul.html
//  Версия: 1.0.2
//  Последнюю версию библиотеки Вы можете скачать по ссылке: http://iarduino.ru/file/491.html
//  Подробное описание функции бибилиотеки доступно по ссылке: https://wiki.iarduino.ru/page/trema-matrix-led/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел.
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_I2C_Matrix_8x8_h																										//
#define iarduino_I2C_Matrix_8x8_h																										//
																																		//
#if defined(ARDUINO) && (ARDUINO >= 100)																								//
#include		<Arduino.h>																												//
#else																																	//
#include		<WProgram.h>																											//
#endif																																	//
																																		//
#include		<iarduino_I2C_Matrix_8x8_I2C.h>																							//	Подключаем файл iarduino_I2C_Matrix_8x8_I2C.h - для работы с шиной I2C		(используя функции структуры iI2C)
																																		//
#define			DEF_CHIP_ID_FLASH		0x3C																							//	ID линейки чипов - константа для всех чипов серии Flash (позволяет идентифицировать принадлежность чипа к серии).
#define			DEF_CHIP_ID_METRO		0xC3																							//	ID линейки чипов - константа для всех чипов серии Metro (позволяет идентифицировать принадлежность чипа к серии).
#define			DEF_MODEL_8X8			0x08																							//	Идентификатор модели - константа.
//				Адреса регистров модуля:																								//
#define			REG_FLAGS_0				0x00																							//	Адрес регистра флагов управления для чтения.
#define			REG_BITS_0				0x01																							//	Адрес регистра битов  управления для чтения и записи.
#define			REG_FLAGS_1				0x02																							//	Адрес регистра флагов управления для чтения.
#define			REG_BITS_1				0x03																							//	Адрес регистра битов  управления для чтения и записи.
#define			REG_MODEL				0x04																							//	Адрес регистра содержащего номер типа модуля.
#define			REG_VERSION				0x05																							//	Адрес регистра содержащего версию прошивки.
#define			REG_ADDRESS				0x06																							//	Адрес регистра содержащего текущий адрес модуля на шине I2C. Если адрес указан с флагом IF-PIN-ADDRES то адрес установится (и запишется в регистр) только при наличии 1 на входе PIN_ADDRES.
#define			REG_CHIP_ID				0x07																							//	Адрес регистра содержащего ID линейки чипов. По данному ID можно определить принадлежность чипа к линейки iarduino.
#define			REG_FREQUENCY			0x08																							//	Адрес регистра содержащего частоту обновления экрана (только для записи).
#define			REG_BRIGHTNESS			0x09																							//	Адрес регистра содержащего яркость свечения дисплея  (только для записи).
#define			REG_8X8_DATA			0x10																							//	Адрес регистра флагов для чтения и записи, далее следуют регистры данных.
#define			REG_8X8_SAVE_AS			0x19																							//	Адрес регистра позволяющего заменить изображение символа в таблице символов на текущее изображение экрана.
#define			REG_8X8_SYMBOL_INPUT	0x1A																							//	Адрес регистра позволяющего вывести изображение символа по его коду.
#define			REG_8X8_TEXT_INPUT		0x1B																							//	Адрес регистра позволяющего дописать текст бегущей строки.
#define			REG_8X8_STEP_LEN		0x1C																							//	Адрес регистра позволяющего установить бегущую строку в указанную позицию.
#define			REG_8X8_TIME_STEP		0x1E																							//	Адрес регистра содержащего время затрачиваемое на один шаг автопрокрутки бегущей строки в сотых долях секунд.
#define			REG_8X8_TIME_PAUSE		0x1F																							//	Адрес регистра содержащего время паузы до повторной автопрокрутки всей бегущей строки в десятых долях секунд.
#define			REG_8X8_TIME_START		0x20																							//	Адрес регистра содержащего время простоя автопрокрутки на первом    символе текста в сотых долях секунд.
#define			REG_8X8_TIME_STOP		0x21																							//	Адрес регистра содержащего время простоя автопрокрутки на последнем символе текста в сотых долях секунд.
#define			REG_8X8_FUNCTIONS		0x22																							//	Адрес регистра позволяющего выполнить функцию анимации по её номеру.
//				Функций анимации ряби:																									//	                                                                                           (0x01) - предварительная очистка        / (0x02) - предварительная закраска
#define			X8_EMPTY_RIPPLES		100																								//	Параметр для функций on()/off()         - анимация ряби        на пустом             фоне. (0x03) - Появление из пустого      фона / (0x04) - Исчезновение в пустой      фон
#define			X8_RIPPLES				101																								//	Параметр для функций fillScr()/clrScr() - анимация ряби        на закрашенном/пустом фоне.
#define			X8_FILLED_RIPPLES		102																								//	Параметр для функций on()/off()         - анимация ряби        на закрашенном        фоне. (0x05) - Появление из закрашенного фона / (0x06) - Исчезновение в закрашенный фон
//				Функций анимации сверху-вниз:																							//
#define			X8_EMPTY_DOWN			104																								//	Параметр для функций on()/off()         - анимация сверху-вниз на пустом             фоне. (0x07) - Появление из пустого      фона / (0x08) - Исчезновение в пустой      фон
#define			X8_DOWN					105																								//	Параметр для функций fillScr()/clrScr() - анимация сверху-вниз на закрашенном/пустом фоне.
#define			X8_FILLED_DOWN			106																								//	Параметр для функций on()/off()         - анимация сверху-вниз на закрашенном        фоне. (0x09) - Появление из закрашенного фона / (0x0A) - Исчезновение в закрашенный фон
//				Функций анимации снизу-вверх:																							//
#define			X8_EMPTY_TOP			108																								//	Параметр для функций on()/off()         - анимация снизу-вверх на пустом             фоне. (0x0B) - Появление из пустого      фона / (0x0C) - Исчезновение в пустой      фон
#define			X8_TOP					109																								//	Параметр для функций fillScr()/clrScr() - анимация снизу-вверх на закрашенном/пустом фоне.
#define			X8_FILLED_TOP			110																								//	Параметр для функций on()/off()         - анимация снизу-вверх на закрашенном        фоне. (0x0D) - Появление из закрашенного фона / (0x0E) - Исчезновение в закрашенный фон
//				Виды памяти для хранения изображений:																					//
#define			X8_IMG_RAM				0																								//	Тип памяти в которой хранится массив изображения - ОЗУ
#define			X8_IMG_ROM				1																								//	Тип памяти в которой хранится массив изображения - ПЗУ
//				Виды поддерживаемых кодировок:																							//
#define			X8_TXT_CP866			0																								//	Название кодировки в которой написан текст для функции print.
#define			X8_TXT_UTF8				1																								//	Название кодировки в которой написан текст для функции print.
#define			X8_TXT_WIN1251			2																								//	Название кодировки в которой написан текст для функции print.
																																		//
class iarduino_I2C_Matrix_8x8{																											//
	public:																																//
	/**	Конструктор класса **/																											//
		iarduino_I2C_Matrix_8x8				(uint8_t address=0){																		//	Конструктор класса													(Параметр: адрес дисплея на шине I2C, если не указан (=0), то адрес будет определён).
											if(address>0x7F){ address>>=1; }															//	Корректируем адрес, если он указан с учётом бита RW.
							valAddrTemp	=	address;																					//	Сохраняем переданный адрес дисплея.
							objI2C		=	new iarduino_I2C;																			//	Переопределяем указатель objI2C на объект производного класса iarduino_I2C.
		}																																//
	/**	Пользовательские функции **/																									//
		bool				begin			(void								);														//	Объявляем  функцию инициализации дисплея							(Параметр:  отсутствует).
		bool				changeAddress	(uint8_t							);														//	Объявляем  функцию смены адреса модуля на шине I2C					(Параметр:  новый адрес модуля).
		bool				reset			(void								);														//	Объявляем  функцию перезагрузки модуля								(Параметр:  отсутствует).
		uint8_t				getAddress		(void								){ return valAddr;			}							//	Определяем функцию возвращающую текущий адрес модуля на шине I2C	(Параметр:  отсутствует).
		uint8_t				getVersion		(void								){ return valVers;			}							//	Определяем функцию возвращающую текущую версию прошивки модуля		(Параметр:  отсутствует).
		uint8_t				getCoding		(void								){ return codingName;		}							//	Определяем функцию возвращающую текущую кодировку текста для print	(Параметр:  отсутствует).
		void				setCoding		(uint8_t i							){ codingName=i;			}							//	Определяем функцию установки кодировки текста для функции print		(Параметр:  название кодировки текста для функции print).
		void				codingDetect	(const char*						);														//	Объявляем  функцию автоматического определения кодировки			(Параметр:  строка состоящая из символа 'п' и символа конца строки.
		void				clrScr			(uint8_t=0							);														//	Объявляем  функцию очистки экрана									(Параметр:  [функция анимации исчезания]).
		void				fillScr			(uint8_t=0							);														//	Объявляем  функцию заливки экрана									(Параметр:  [функция анимации исчезания]).
		void				invScr			(void								);														//	Объявляем  функцию инверсии текущего изображения					(Параметр:  отсутствует).
		void				drawImage		(uint8_t*	, uint8_t=0, uint8_t=0	);														//	Объявляем  функцию вывода изображения на дисплей					(Параметры: массив с изображением, [функция анимации появления] , и или [тип памяти массива]).
		void				getImage		(uint8_t*							);														//	Объявляем  функцию получения текущего изображения в массив			(Параметр:  массив для изображения).
		void				print			(const char	 i, uint8_t j=0			){ _printStr(String (i),j);	}							//	Определяем функцию вывода символа или бегущей строки				(Параметры: символ/текст,  [функция анимации появления]).
		void				print			(char*       i, uint8_t j=0			){ _printStr(String (i),j);	}							//	Определяем функцию вывода символа или бегущей строки				(Параметры: символ/текст,  [функция анимации появления]).
		void				print			(const char* i, uint8_t j=0			){ _printStr(String (i),j);	}							//	Определяем функцию вывода символа или бегущей строки				(Параметры: символ/текст,  [функция анимации появления]).
		void				print			(String      i, uint8_t j=0			){ _printStr(        i ,j);	}							//	Определяем функцию вывода символа или бегущей строки				(Параметры: символ/текст,  [функция анимации появления]).
		void				print			(int8_t      i, uint8_t j=0			){ _printNum(uint8_t(i),j);	}							//	Определяем функцию вывода цифры										(Параметры: цифра,         [функция анимации появления]).
		void				print			(uint8_t     i, uint8_t j=0			){ _printNum(uint8_t(i),j);	}							//	Определяем функцию вывода цифры										(Параметры: цифра,         [функция анимации появления]).
		void				print			(int16_t     i, uint8_t j=0			){ _printNum(uint8_t(i),j);	}							//	Определяем функцию вывода цифры										(Параметры: цифра,         [функция анимации появления]).
		void				print			(uint16_t    i, uint8_t j=0			){ _printNum(uint8_t(i),j);	}							//	Определяем функцию вывода цифры										(Параметры: цифра,         [функция анимации появления]).
		void				print			(int32_t     i, uint8_t j=0			){ _printNum(uint8_t(i),j);	}							//	Определяем функцию вывода цифры										(Параметры: цифра,         [функция анимации появления]).
		void				print			(uint32_t    i, uint8_t j=0			){ _printNum(uint8_t(i),j); }							//	Определяем функцию вывода цифры										(Параметры: цифра,         [функция анимации появления]).
		void				autoScroll		(uint8_t      , uint16_t=0			);														//	Объявляем  функцию установки скорости прокрутки и паузы между ними	(Параметр:  скорость от 0 до 255, [пауза от 0 до 25500 мс]). Если первый параметр = 0, то бегущая строка остановится. Если второй параметр 0 (или лтстутсвует), то бегущая строка будет прокручена однократно.
		void				scrollPos		(uint16_t							);														//	Объявляем  функцию установки позиции смещения бегущей строки		(Параметр:  позиция) либо в пикселях, либо в символах, зависит от scrollMod().
		void				scrollDir		(bool								);														//	Объявляем  функцию выбора направления движения бегущей строки		(Параметр:  направление) 1-право/0-лево.
		void				scrollMod		(bool								);														//	Объявляем  функцию выбора режима смещения бегущей строки			(Параметр:  режим)       1-посимвольный/0-попиксельный.
		void				scrollStep		(void								);														//	Объявляем  функцию пошагового сдвига бегущей строки					(Параметр:  отсутствует) сдвиг на один scrollMod() в направлении scrollDir().
		void				setTimeIdleFirst(uint16_t							);														//	Объявляем  функцию установки простоя на первом символе бегущей стр	(Параметр:  время простоя в мс).
		void				setTimeIdleLast	(uint16_t							);														//	Объявляем  функцию установки простоя на послед символе бегущей стр	(Параметр:  время простоя в мс).
		uint16_t			getScroolLen	(void								){ return stringLen;		 }							//	Определяем функцию получения количества символов в бегущей строке   (Параметр:  отсутствует).
		uint16_t			getScroolWidth	(void								){ return uint16_t(stringLen)*(uint16_t(charWidth)+uint16_t(charInterval));}	//	Определяем функцию получения количества символов в бегущей строке   (Параметр:  отсутствует).
		void				angle			(uint16_t							);														//	Объявляем  функцию поворота экрана									(Параметр:  угол°).
		void				fps				(uint8_t							);														//	Объявляем  функцию установки скорости обновления экрана				(Параметр:  количество кадров в секунду).
		void				bright			(uint8_t							);														//	Объявляем  функцию установки яркости экрана							(Параметр:  яркость).
		void				changeChar		(uint8_t							);														//	Объявляем  функцию смены изображения символа						(Параметр:  код символа изображение которого требуется изменить).
		void				setCharWidth	(uint8_t							);														//	Объявляем  функцию установки ширины изображений всех символов		(Параметр:  ширина в пикселях от 3 до 7 включительно). Изменение этого значения приведёт к искажению изображений всех символов
		uint8_t				getCharWidth	(void								){ return charWidth;		}							//	Объявляем  функцию получения ширины изображений всех символов		(Параметр:  отсутствует).
		void				setCharInterval	(uint8_t							);														//	Объявляем  функцию установки межсимвольного интервала				(Параметр:  межсимвольный интервал в пикселях).
		uint8_t				getCharInterval	(void								){ return charInterval;		}							//	Объявляем  функцию получения межсимвольного интервала				(Параметр:  отсутствует).
		void				setCharIndent	(uint8_t							);														//	Объявляем  функцию установки отступа от левого края до символа		(Параметр:  отступ в пикселях от 0 до 5).
		uint8_t				getCharIndent	(void								){ return charIndent;		}							//	Объявляем  функцию получения отступа от левого края до символа		(Параметр:  отсутствует).
																																		//
	private:																															//
	/**	Внутренние переменные **/																										//
		uint8_t				valAddrTemp	=	0;																							//	Определяем переменную для хранения адреса модуля на шине I2C который был указан, но не был проверен.
		uint8_t				valAddr		=	0;																							//	Определяем переменную для хранения адреса модуля на шине I2C.
		uint8_t				valVers		=	0;																							//	Определяем переменную для хранения версии прошивки модуля.
		uint8_t				codingName	=	X8_TXT_UTF8;																				//	Определяем переменную для хранения текущей кодировки.
		uint8_t				data[8];																									//	Объявляем  массив     для хранения получаемых/передаваемых данных.
		uint8_t				charWidth	=	0;																							//	Определяем переменную для хранения ширины изображений символов.
		uint8_t				charInterval=	0;																							//	Определяем переменную для хранения мажсимвольного интервала.
		uint8_t				charIndent	=	0;																							//	Определяем переменную для хранения отступа от левого края экрана до символа.
		uint16_t			stringLen	=	12;																							//	Определяем переменную для хранения количества символов в бегущей строке.
		iarduino_I2C_BASE*	objI2C;																										//	Объявляем  указатель на объект полиморфного класса iarduino_I2C_BASE, но в конструкторе данного класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C.
	/**	Внутренние функции **/																											//
		bool				_readBytes		(uint8_t	, uint8_t				);														//	Объявляем  функцию чтения данных в  массив  data					(Параметры:  номер первого регистра, количество байт).
		bool				_writeBytes		(uint8_t	, uint8_t, uint8_t=0	);														//	Объявляем  функцию записи данных из массива data					(Параметры:  номер первого регистра, количество байт, номер первого элемента массива data).
		void				_printNum		(uint8_t	, uint8_t				);														//	Объявляем  функцию вывода цифры на дисплей							(Параметры:  цифра, функция анимации появления).
		void				_printStr		(String		, uint8_t				);														//	Объявляем  функцию вывода символа или бегущей строки на дисплей		(Параметры:  код символа или строка, функция анимации появления).
		void				_setChar0		(void								);														//	Объявляем  функцию установки ширины, интервала и отступа символов	(Параметр:   отсутствует).
		String				_codingCP866	(String								);														//	Объявляем  функцию преобразования кодировки в CP866					(Параметр:   строка в кодировке codingName).
};																																		//
																																		//
#endif																																	//