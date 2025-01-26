#include "Double.h"
#include "Int.h"
#include "String.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <istream>
#include <numeric>
#include <ostream>
#include <vector>

/*
 * Необходимо предусмотреть создание заголовка таблицы со столбцами объектов
 * выбранных типов, добавление, удаление, редактирование строк, сортировку по
 * любому столбцу, сохранение и загрузку таблицы (структуры и содержимого)
 * в текстовом файле.
 */

/*Список студентов*/
class StudentList {
public:
	/*Добавление нового студента по готовым данным*/
	StudentList & add(Int const & N,	   /*Номер студента*/
			  String const & Surname,  /*Фамилия*/
			  String const & Name,	   /*Имя*/
			  String const & Patronim, /*Отчество*/
			  Int const & Mark1,	   /*Оценка студента*/
			  Int const & Mark2,	   /*Оценка студента*/
			  Int const & Mark3,	   /*Оценка студента*/
			  Int const & Mark4,	   /*Оценка студента*/
			  Int const & Mark5	   /*Оценка студента*/
	)
	{
		std::array<Int, mcount> marks{Mark1, Mark2, Mark3, Mark4,
					      Mark5};
		add_(Student(N, Surname, Name, Patronim, AvgMark_(marks),
			     marks));
		return *this;
	}

	/*Ввод одной записи*/
	StudentList & enter(std::istream & ist);

	/*Чтение из текстового потока*/
	friend std::istream & operator>>(std::istream &, StudentList &);

	/*Вывод без форматирования*/
	friend std::ostream & operator<<(std::ostream &, StudentList const &);

	/*Повторный ввод записи с соответствующим номером*/
	bool ReenterStudentWithN(std::istream &, int);

	/*Повторный ввод записи с соответствующим именем*/
	bool ReenterStudentWithName(std::istream &, String const &);

	/*Повторный ввод записи с соответствующим отчеством*/
	bool ReenterStudentWithPatronim(std::istream &, String const &);

	/*Повторный ввод записи с соответствующей фамилией*/
	bool ReenterStudentWithSurname(std::istream &, String const &);

	/*Удаление записи с соответствующим номером*/
	bool DeleteStudentWithN(int);

	/*Удаление записи с соответствующим именем*/
	bool DeleteStudentWithName(String const &);

	/*Удаление записи с соответствующим отчеством*/
	bool DeleteStudentWithPatronim(String const &);

	/*Удаление записи с соответствующей фамилией*/
	bool DeleteStudentWithSurname(String const &);

	/*Сортировка списка по номерам*/
	StudentList & SortStudentByNDesc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::N));
		return *this;
	}

	/*Сортировка списка по именам*/
	StudentList & SortStudentByNameDesc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::NAME));
		return *this;
	}

	/*Сортировка списка по отчествам*/
	StudentList & SortStudentByPatronimDesc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::PATRONIM));
		return *this;
	}

	/*Сортировка списка по фамилиям*/
	StudentList & SortStudentBySurnameDesc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::SURNAME));
		return *this;
	}

	/*Сортировка списка по средним оценкам*/
	StudentList & SortStudentByAvgMarkDesc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::AVG));
		return *this;
	}

	/*Сортировка списка по оценкам 1*/
	StudentList & SortStudentByMark1Desc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::M1));
		return *this;
	}

	/*Сортировка списка по оценкам 2*/
	StudentList & SortStudentByMark2Desc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::M2));
		return *this;
	}

	/*Сортировка списка по оценкам 3*/
	StudentList & SortStudentByMark3Desc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::M3));
		return *this;
	}

	/*Сортировка списка по оценкам 4*/
	StudentList & SortStudentByMark4Desc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::M4));
		return *this;
	}

	/*Сортировка списка по оценкам 5*/
	StudentList & SortStudentByMark5Desc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::DESC,
				   SortFunc::SortField::M5));
		return *this;
	}

	/*Сортировка списка по номерам*/
	StudentList & SortStudentByNAsc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::N));
		return *this;
	}

	/*Сортировка списка по именам*/
	StudentList & SortStudentByNameAsc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::NAME));
		return *this;
	}

	/*Сортировка списка по отчествам*/
	StudentList & SortStudentByPatronimAsc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::PATRONIM));
		return *this;
	}

	/*Сортировка списка по фамилиям*/
	StudentList & SortStudentBySurnameAsc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::SURNAME));
		return *this;
	}

	/*Сортировка списка по средним оценкам*/
	StudentList & SortStudentByAvgMarkAsc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::AVG));
		return *this;
	}

	/*Сортировка списка по оценкам 1*/
	StudentList & SortStudentByMark1Asc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::M1));
		return *this;
	}

	/*Сортировка списка по оценкам 2*/
	StudentList & SortStudentByMark2Asc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::M2));
		return *this;
	}

	/*Сортировка списка по оценкам 3*/
	StudentList & SortStudentByMark3Asc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::M3));
		return *this;
	}

	/*Сортировка списка по оценкам 4*/
	StudentList & SortStudentByMark4Asc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::M4));
		return *this;
	}

	/*Сортировка списка по оценкам 5*/
	StudentList & SortStudentByMark5Asc()
	{
		std::sort(list_.begin(), list_.end(),
			  SortFunc(SortFunc::SortOrder::ASC,
				   SortFunc::SortField::M5));
		return *this;
	}

private:
	static constexpr auto mcount{5ul}; /*Число оценок*/

	/*Запись студента*/
	struct Student {
		Int N;			       /*Номер студента*/
		String Surname,		       /*Фамилия*/
			Name,		       /*Имя*/
			Patronim;	       /*Отчество*/
		Double AvgMark;		       /*Средний бал*/
		std::array<Int, mcount> Marks; /*Оценки студента*/

		/*Конструктор записи*/
		Student(Int const & N,
			String const & Surname,
			String const & Name,
			String const & Patronim,
			Double const & AvgMark,
			std::array<Int, mcount> const & Marks)
			: N{N}, Surname{Surname}, Name{Name},
			  Patronim{Patronim}, AvgMark{AvgMark}, Marks{Marks}
		{
		}

		/*Пустой конструктор*/
		Student() {}
	};

	struct SortFunc {
		enum class SortField {
			N,
			SURNAME,
			NAME,
			PATRONIM,
			AVG,
			M1,
			M2,
			M3,
			M4,
			M5
		} sf;
		/*Порядок сотрировки*/
		enum class SortOrder {
			DESC = -1,
			ASC = 1
		} so;

		SortFunc(SortOrder so, SortField sf) : sf{sf}, so{so} {}

		bool operator()(Student const & a, Student const & b)
		{
			switch (sf) {
			case SortFunc::SortField::N:
				return intsort(a.N, b.N);
			case SortFunc::SortField::SURNAME:
				return intsort(a.Surname, b.Surname);
			case SortFunc::SortField::NAME:
				return intsort(a.Name, b.Name);
			case SortFunc::SortField::PATRONIM:
				return intsort(a.Patronim, b.Patronim);
			case SortFunc::SortField::AVG:
				return intsort(a.AvgMark, b.AvgMark);
			case SortFunc::SortField::M1:
				return intsort(a.Marks[0], b.Marks[0]);
			case SortFunc::SortField::M2:
				return intsort(a.Marks[1], b.Marks[1]);
			case SortFunc::SortField::M3:
				return intsort(a.Marks[2], b.Marks[2]);
			case SortFunc::SortField::M4:
				return intsort(a.Marks[3], b.Marks[3]);
			case SortFunc::SortField::M5:
				return intsort(a.Marks[4], b.Marks[4]);
			}
		}

		template <class T> bool intsort(T const & a, T const & b)
		{
			if (so == SortOrder::ASC)
				return a < b;
			/*else*/ return a > b;
		}
	};

	/*Список студентов*/
	std::vector<StudentList::Student> list_;

	/*Добавление готовой записи со студентом*/
	StudentList & add_(Student const & A);

	/*Подсчёт средней оценки*/
	Double AvgMark_(std::array<Int, mcount> const & marks)
	{
		Int sum{};
		for (auto & mark : marks)
			sum += mark;

		return sum.get() / static_cast<double>(marks.size());
	}

	/*Поиск записи с соответствующим номером*/
	int FindStudentByN(int) const;

	/*Поиск записи с соответствующим именем*/
	int FindStudentByName(String const &) const;

	/*Поиск записи с соответствующим номером*/
	int FindStudentByPatronim(String const &) const;

	/*Поиск записи с соответствующей фамилией*/
	int FindStudentBySurname(String const &) const;
};
