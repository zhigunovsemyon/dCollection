#include "StudentList.h"

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

StudentList & StudentList::enter(std::istream & ist)
{
	Student tmp{};
	ist >> tmp.N >> tmp.Surname >> tmp.Name >> tmp.Patronim;
	for (auto & mark : tmp.Marks)
		ist >> mark;

	if (ist.good()) {
		tmp.AvgMark = AvgMark_(tmp.Marks);
		add_(tmp);
	}

	return *this;
}

/*Вывод без форматирования*/
std::ostream & operator<<(std::ostream & ost, StudentList const & list)
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

/*Чтение из текстового потока*/
std::istream & operator>>(std::istream & ist, StudentList & list)
{
	do {
		StudentList::Student tmp{};
	ist >> tmp.N >> tmp.Surname >> tmp.Name;
	ist >> tmp.Patronim >> tmp.AvgMark;
	for (auto & mark : tmp.Marks)
		ist >> mark;

	if (ist.good()) {
		list.add_(tmp);
	}
	} while (ist.good());

	return ist;
}
