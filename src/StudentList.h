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
	StudentList & enter(std::istream & ist)
	{
		Student tmp{};
		ist >> tmp.N >> tmp.Surname >> tmp.Name >> tmp.Patronim;
		for (auto & mark : tmp.Marks)
			ist >> mark;

		if(ist.good()){
			tmp.AvgMark = AvgMark_(tmp.Marks);
			add_(tmp);
		}

		return *this;
	}

	/*Вывод без форматирования*/
	friend std::ostream & operator<<(std::ostream & ost,
					 StudentList const & list)
	{
		for (auto & rec : list.list_) {
			ost << rec.N << ' ' << rec.Surname << ' ' << rec.Name;
			ost << ' ' << rec.Patronim << ' ' << rec.AvgMark << ' ';
			for (auto & mark : rec.Marks)
				ost << mark << ' ';
			ost << '\n';
		}

		return ost;
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
		Student(Int  const & N,
			String  const & Surname,
			String  const & Name,
			String  const & Patronim,
			Double  const & AvgMark,
			std::array<Int, mcount>  const & Marks)
			: N{N}, Surname{Surname}, Name{Name},
			  Patronim{Patronim}, AvgMark{AvgMark}, Marks{Marks}
		{
		}
		/*Пустой конструктор*/
		Student() {}
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

	Int MaxSurnameWidth_{0},      /*Самая широкая фамилия*/
		MaxNameWidth_{0},     /*Самое широкое имя*/
		MaxPatronimWidth_{0}; /*Самое широкое отчество*/
};

StudentList & StudentList::add_(Student const & A)
{
	MaxNameWidth_ = static_cast<int>(std::max(
		static_cast<size_t>(MaxNameWidth_.get()), A.Name.length()));
	MaxSurnameWidth_ = static_cast<int>(
		std::max(static_cast<size_t>(MaxSurnameWidth_.get()),
			 A.Surname.length()));
	MaxPatronimWidth_ = static_cast<int>(
		std::max(static_cast<size_t>(MaxPatronimWidth_.get()),
			 A.Patronim.length()));

	list_.push_back(A);
	return *this;
}
