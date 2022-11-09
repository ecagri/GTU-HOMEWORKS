#include <iostream>
#include <vector>
using std::vector;
using std::ostream;
using std::endl;

namespace DATES{
	class DayofYearSet{
	public:
		class DayofYear{
		public:
			DayofYear(int, int);
			explicit DayofYear(int);
			DayofYear();
			int get_day() const;
			int get_month() const;
			friend bool operator==(DayofYearSet::DayofYear, DayofYearSet::DayofYear);
		private:
			int day;
			int month;
			void set_day();
			void set_month();
		};
		explicit DayofYearSet(vector <DayofYearSet::DayofYear>);
		DayofYearSet(DayofYearSet&);
		DayofYearSet();
		~DayofYearSet();
		void add(int, int);
		void remove(int, int);
		int get_size() const;
		DayofYear operator[](int) const;
		DayofYearSet& operator=(const DayofYearSet&);
		friend DayofYearSet& operator+(DayofYearSet&, DayofYearSet);
		friend DayofYearSet& operator-(DayofYearSet&, DayofYearSet);
		friend DayofYearSet& operator^(DayofYearSet&, DayofYearSet);
		friend DayofYearSet& operator!(DayofYearSet&);
		friend ostream& operator<<(ostream&, DayofYearSet&);
		friend ostream& operator<<(ostream&, DayofYearSet::DayofYear);
		friend bool operator==(DayofYearSet, DayofYearSet);
		friend bool operator!=(DayofYearSet, DayofYearSet);
		static int number_of_elements;
		static void announce();
	private:
		int size_of_array = 0;
		DayofYear * days = nullptr;
		bool is_exist(DayofYearSet::DayofYear) const;
		DayofYear * get_day_array();
	};
}