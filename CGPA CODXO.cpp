#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct Course {
    double credits;
    double gradePoints;
};

class CGPACalculator {
private:
    vector<vector<Course>> semesters; // Vector of vectors to store courses for each semester
    bool isFail = false;

public:
    void addCourses(int semesterIndex, int count) {
        double credits, grade;
        for (int i = 1; i <= count; ++i) {
            cout << "Enter credits and grade points for course " << i << " in Semester " << semesterIndex << ": ";
            cin >> credits >> grade;
            semesters[semesterIndex - 1].push_back({credits, credits * grade});
        }
    }

    double calculateGPA(int semesterIndex) {
        const vector<Course>& courses = semesters[semesterIndex - 1];
        if (courses.empty()) {
            return 0.0;
        }

        double totalCredits = 0.0;
        double totalGradePoints = 0.0;

        for (const auto& course : courses) {
            totalCredits += course.credits;
            totalGradePoints += course.gradePoints;
        }

        return totalGradePoints / totalCredits;
    }

    void displayResult(double GPA) {
        cout << fixed << setprecision(2);
        cout << "GPA: " << GPA << endl;
        if (GPA < 2.2) {
            cout << "Sorry, you failed. Minimum GPA required is 2.20." << endl;
            isFail = true;
        }
    }

    bool isFailed() const {
        return isFail;
    }

    void clearCourses() {
        semesters.clear();
        isFail = false;
    }

    void initializeSemesters(int numSemesters) {
        semesters.resize(numSemesters);
    }
};

int main() {
    CGPACalculator calculator;
    char choice;

    cout << "\tWelcome to CGPA Calculator!" << endl;
    cout << "----------------------------------" << endl;

    cout << "Enter number of semesters: ";
    int numSemesters;
    cin >> numSemesters;

    calculator.initializeSemesters(numSemesters);

    for (int i = 1; i <= numSemesters; ++i) {
        int coursesCount;
        cout << "Enter number of courses for Semester " << i << ": ";
        cin >> coursesCount;

        calculator.addCourses(i, coursesCount);

        double GPA = calculator.calculateGPA(i);
        cout << "Semester " << i << " ";
        calculator.displayResult(GPA);

        if (calculator.isFailed()) {
            break;
        }

        calculator.clearCourses();
    }

    double cumulativeCGPA = 0.0;
    for (int i = 1; i <= numSemesters; ++i) {
        cumulativeCGPA += calculator.calculateGPA(i);
    }

    cumulativeCGPA /= numSemesters;
    cout << "Cumulative CGPA: " << fixed << setprecision(2) << cumulativeCGPA << endl;

    return 0;
}
