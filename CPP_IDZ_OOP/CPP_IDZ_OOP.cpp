/* ЗАДАНИЕ
5. Система обліку пацієнтів лікарні
Розробити систему обліку пацієнтів лікарні (не поліклініки!). Забезпечити прийом та розподіл пацієнтів, прив'язку до лікаря, переведення із
палати в палату.
Сутності: пацієнти, хвороби, палати, лікарі, історія хвороби…
Функції: заповнення довідників, прийом пацієнта, ведення картки
пацієнта, виписка…
Вихідні документи: список пацієнтів, список лікарів, картка пацієнта…
*/

/* СУЩНОСТИ
Со стороны пациента: Болезни, лечащие врачи, история болезни, койка, карточка пациента
Со стороны врача: должность, пациенты под наблюдением, указание рабочего кабинета
Со стороны больницы: кол-во доступных коек, список палат с статистикой занятости, список пациентов на лечении...
...список врачей, карты пациентов
*/

/* НЕОБХОДИМЫЕ ФУНКЦИИ
Для пациента: нет, только содержание в виде информации;
Для врача: приписка больных, изменение кабинета...
... открепление от пациента.
Для больницы: Оформление карты пациента, добавление нового пациента, доступ к списку врачей, доступ к списку пациентов...
... доступ к карточкам пациентов, добавление нового врача, удаление врача из базы...
... доступ к списку коек, добавление к кол-ву коек, уменьшение кол-ва коек, выписка пациента.
*/

/* СТРУКТУРЫ
Пациент: Карточка пациента, история болезни, список лечащих врачей.
	Карточка пациента: инфо по документу.
	
Врач: ФИО, должность, кабинет, список пациентов.
Больница: Список коек, список пациентов, список врачей, список карт пациентов.
*/


//Добавить счетчики для врачей, пациентов, больниц

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;
class Patient {

public:
	struct PatientInfo {
		struct patientsCard {
			string patientName = "Не вказане ім'я пацієнта";
			string sex = "Не вказаний пол пацієнта";
			string dateOfBirth = "Не вказана дата народження пацієнта";
			string phoneNumber = "Не вказаний номер телефнону пацієнта";
			string placeOfLiving = "Не вказане місце проживання пацієнта";
			string placeOfWorkAndProfession = "Не вказане місце праці та посада";
			string DispensaryGroup = "Не вказана діспенсерна група";
			string continget = "Не вказаний контінгент";
			string otherBenefits = "Не вказані інші пільги";
			string numberOfBenefitsDocument = "Не вказаний номер пільгового посвідчення";
			string dateOfArival = "Не вказана дата взяття на облік";
			string reasonOfArival = "Не вказана причина взяття на облік";
			string dateOfDischarge = "Не вказана дата зняття з обліку";
			string reasonOfDischarge = "Не вказана причина зняття з обліку";
		};

		struct illnesHistory {
			string nameOfIllnes = "Не вказано";
			string illnesDescription = "Не вказано";
			string prescribedTreatment = "Не вказано";
			string currentWard = "";
			string listOfAttachedDoctors = "";
		};

	};
	PatientInfo patientsCredentials;
	PatientInfo::patientsCard patientsCardInfo;
	PatientInfo::illnesHistory patientsIllnesHistory;
	Patient();
};

Patient::Patient() {

}


class Doctor {

public:
	struct DoctorInfo{
		string doctorInitials = "Не вказане ім'я доктора";
		string doctorProfession = "Не вказана спеціальність доктора";
	};
	DoctorInfo doctorsCredentials;
	Doctor();
};

Doctor::Doctor() {

}




class Hospital {

public:
	struct HospitalInfo {
		Doctor* ListOfDoctors = new Doctor[1];
		Patient* ListOfPatients = new Patient[1];
		struct WardList {
			string nameOfWard = "Не вказане ім'я палати";
			short amountOfBunks = 0;
			short accessibleBunks = 0;
		};
		WardList* wardList = new WardList[1];
	};
	HospitalInfo HospitalInfoData;
	Hospital();
	~Hospital();
	short amountOfPatients = 0;
	short amountOfDoctors = 0;
	short amountOfWards = 0;
	void OnClosure();
	void GUI();
	void syncFiles(); 
	void outListOfPatients();
	void outListOfWards();
	void outListOfDoctors();
	void outListOfPatientsCards(short idOfPatient);
	void outPatientsIllnesHistory(short idOfPatient);
	void addPatientToList(bool fullNew);
	void redactPatientsCard(bool isNew, short idOfPatient);
	void redactPatientsIllnesHistory(short idOfCard);
	void redactWardList(bool fullNew, short idOfWard);
	void redactDoctorList(bool fullNew, short idOfDoctor);
	void removePatientFromList();
	void addDoctorToList(bool fullNew);
	void removeDoctorFromList();
	void addWardToList(bool fullNew);
	void removeWardFromList();
};

Hospital::Hospital() {
	string inputString;
	string generalVariablesFile = "GeneralVariablesFile.txt";
	string listOfPatientsCards = "listOfPatientsCards.txt";
	string listOfDoctors = "listOfDoctors.txt";
	string listOfWards = "listOfWards.txt";
	fstream appendFileToWorkWith;
	appendFileToWorkWith.open(generalVariablesFile, fstream::in | fstream::out | fstream::app);
	if (!appendFileToWorkWith) {
		printf("\nПроблема з відкриттям файла! Завершую роботу програми...");
		exit(1);
	}
	if (appendFileToWorkWith.peek() == std::ifstream::traits_type::eof()) {
		printf("\nФайл пустой або не знайден, створен пустой файл з початковими значеннями.");
		appendFileToWorkWith.seekg(0, ios::beg);
		appendFileToWorkWith << "Кількість пацієнтів у лікарні: 0\n";
		appendFileToWorkWith << "Кількість лікарів у лікарні: 0\n";
		appendFileToWorkWith << "Кількість палат у лікарні: 0\n";
		amountOfPatients = amountOfDoctors = amountOfWards = 0;
	}
	else {
		printf("\nФайл знайдено! Приймає дані з файлу...\n");
		getline(appendFileToWorkWith, inputString);
		inputString.erase(inputString.find("Кількість пацієнтів у лікарні: "), strlen("Кількість пацієнтів у лікарні: "));
		amountOfPatients = stoi(inputString);
		getline(appendFileToWorkWith, inputString);
		inputString.erase(inputString.find("Кількість лікарів у лікарні: "), strlen("Кількість лікарів у лікарні: "));
		amountOfDoctors = stoi(inputString);
		getline(appendFileToWorkWith, inputString);
		inputString.erase(inputString.find("Кількість палат у лікарні: "), strlen("Кількість палат у лікарні: "));
		amountOfWards = stoi(inputString);
	}
	appendFileToWorkWith.close();

	appendFileToWorkWith.open(listOfPatientsCards, fstream::in | fstream::out | fstream::app);
	if (!appendFileToWorkWith) {
		printf("\nПроблема з відкриттям файла! Завершую роботу програми...");
		exit(1);
	}
	if (amountOfPatients == 0 && appendFileToWorkWith.peek() != std::ifstream::traits_type::eof()) {
		printf("\n     Незбіжність даних о лікарях та їх фактичних даних, онуляємо значення.");
		appendFileToWorkWith.close();
		appendFileToWorkWith.open(listOfPatientsCards, fstream::in | fstream::out | fstream::trunc);
	}
	if (appendFileToWorkWith.peek() == std::ifstream::traits_type::eof()) {
		printf("\nФайл з картками пустой або не знайден, створен пустой файл з початковими значеннями.");
		if (amountOfPatients != 0) {
			printf("\n     Незбіжність даних о лікарях та їх фактичних даних, онуляємо значення.");
			appendFileToWorkWith.close();
			appendFileToWorkWith.open(generalVariablesFile, fstream::in | fstream::out | fstream::trunc);
			appendFileToWorkWith.seekg(0, ios::beg);
			appendFileToWorkWith << "Кількість пацієнтів у лікарні: 0\n";
			appendFileToWorkWith << "Кількість лікарів у лікарні: " << amountOfDoctors << "\n";
			appendFileToWorkWith << "Кількість палат у лікарні: " << amountOfWards << "\n";
			amountOfPatients = 0;
		}
	}
	else {
		printf("\nФайл знайдено! Приймає дані з файлу...\n");
		delete[] HospitalInfoData.ListOfPatients;
		HospitalInfoData.ListOfPatients = new Patient[amountOfPatients];
		appendFileToWorkWith.seekg(0, ios::beg);
		for (int i = 0; i < amountOfPatients; i++) {
			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Ім'я пацієнта: "), strlen("Ім'я пацієнта: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.patientName = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Стать паціента: "), strlen("Стать паціента: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.sex = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("День народження: "), strlen("День народження: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.dateOfBirth = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Номер телефону: "), strlen("Номер телефону: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.phoneNumber = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Місце проживання: "), strlen("Місце проживання: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.placeOfLiving = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Місце роботи та посада: "), strlen("Місце роботи та посада: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.placeOfWorkAndProfession = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Діспансерна група: "), strlen("Діспансерна група: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.DispensaryGroup = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Контінгенти: "), strlen("Контінгенти: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.continget = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Інші пільгові категорії: "), strlen("Інші пільгові категорії: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.otherBenefits = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Номер пільгового посвідчення: "), strlen("Номер пільгового посвідчення: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.numberOfBenefitsDocument = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Узятий на облік: "), strlen("Узятий на облік: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.dateOfArival = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Причина взяття на облік: "), strlen("Причина взяття на облік: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.reasonOfArival = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Знятий з обліку: "), strlen("Знятий з обліку: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.dateOfDischarge = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Причина зняття з обліку: "), strlen("Причина зняття з обліку: "));
			HospitalInfoData.ListOfPatients[i].patientsCardInfo.reasonOfDischarge = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Хвороба: "), strlen("Хвороба: "));
			HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.nameOfIllnes = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Історія хвороби: "), strlen("Історія хвороби: "));
			HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.illnesDescription = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Приписанне лікування: "), strlen("Приписанне лікування: "));
			HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.prescribedTreatment = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Приписанна палата: "), strlen("Приписанна палата: "));
			HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.currentWard = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Прив'язанні лікарі: "), strlen("Прив'язанні лікарі: "));
			HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors = inputString;

			getline(appendFileToWorkWith, inputString);
		}
	}

	appendFileToWorkWith.close();

	appendFileToWorkWith.open(listOfDoctors, fstream::in | fstream::out | fstream::app);
	if (!appendFileToWorkWith) {
		printf("\nПроблема з відкриттям файла! Завершую роботу програми...");
		exit(1);
	}
	if (amountOfDoctors == 0 && appendFileToWorkWith.peek() != std::ifstream::traits_type::eof()) {
		printf("\n     Незбіжність даних о докторах та їх фактичних даних, онуляємо значення.");
		appendFileToWorkWith.close();
		appendFileToWorkWith.open(listOfDoctors, fstream::in | fstream::out | fstream::trunc);
	}
	if (appendFileToWorkWith.peek() == std::ifstream::traits_type::eof()) {
		printf("\nФайл з данними лікарів пустой або не знайден, створен пустой файл з початковими значеннями.");
		if (amountOfPatients != 0) {
			printf("\n     Незбіжність даних о докторах та їх фактичних даних, онуляємо значення.");
			appendFileToWorkWith.close();
			appendFileToWorkWith.open(generalVariablesFile, fstream::in | fstream::out | fstream::trunc);
			appendFileToWorkWith.seekg(0, ios::beg);
			appendFileToWorkWith << "Кількість пацієнтів у лікарні: " << amountOfPatients << "\n";
			appendFileToWorkWith << "Кількість лікарів у лікарні: 0" << "\n";
			appendFileToWorkWith << "Кількість палат у лікарні: " << amountOfWards << "\n";
			amountOfDoctors = 0;
		}
	}
	else {
		printf("\nФайл знайдено! Приймає дані з файлу...\n");
		delete[] HospitalInfoData.ListOfDoctors;
		HospitalInfoData.ListOfDoctors = new Doctor[amountOfDoctors];
		appendFileToWorkWith.seekg(0, ios::beg);
		for (int i = 0; i < amountOfDoctors; i++) {
			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Ім'я доктора:"), strlen("Ім'я доктора:"));
			HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorInitials = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Спеціальність: "), strlen("Спеціальність: "));
			HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorProfession = inputString;

			getline(appendFileToWorkWith, inputString);
		}
	}
	appendFileToWorkWith.close();

	appendFileToWorkWith.open(listOfWards, fstream::in | fstream::out | fstream::app);
	if (!appendFileToWorkWith) {
		printf("\nПроблема з відкриттям файла! Завершую роботу програми...");
		exit(1);
	}
	if (amountOfWards == 0 && appendFileToWorkWith.peek() != std::ifstream::traits_type::eof()) {
		printf("\n     Незбіжність даних палат та їх фактичних даних, онуляємо значення.");
		appendFileToWorkWith.close();
		appendFileToWorkWith.open(listOfWards, fstream::in | fstream::out | fstream::trunc);
	}
	if (appendFileToWorkWith.peek() == std::ifstream::traits_type::eof()) {
		printf("\nФайл з даними палат пустий або не знайден, створен пустий файл з початковими значеннями.");
		if (amountOfPatients != 0) {
			printf("\n     Незбіжність даних палат та їх фактичних даних, онуляємо значення.");
			appendFileToWorkWith.close();
			appendFileToWorkWith.open(generalVariablesFile, fstream::in | fstream::out | fstream::trunc);
			appendFileToWorkWith.seekg(0, ios::beg);
			appendFileToWorkWith << "Кількість пацієнтів у лікарні: " << amountOfPatients << "\n";
			appendFileToWorkWith << "Кількість лікарів у лікарні: " << amountOfDoctors << "\n";
			appendFileToWorkWith << "Кількість палат у лікарні: 0" << "\n";
			amountOfWards = 0;
		}
	}
	else {
		printf("\nФайл знайдено! Приймає дані з файлу...\n");
		delete[] HospitalInfoData.wardList;
		HospitalInfoData.wardList = new HospitalInfo::WardList[amountOfWards];
		appendFileToWorkWith.seekg(0, ios::beg);
		for (int i = 0; i < amountOfWards; i++) {
			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("Назва палати: "), strlen("Назва палати: "));
			HospitalInfoData.wardList[i].nameOfWard = inputString;

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("	Загальна кількість ліжок: "), strlen("	Загальна кількість ліжок: "));
			HospitalInfoData.wardList[i].amountOfBunks = stoi(inputString);

			getline(appendFileToWorkWith, inputString);
			inputString.erase(inputString.find("	Вільна кількість ліжок: "), strlen("	Вільна кількість ліжок: "));
			HospitalInfoData.wardList[i].accessibleBunks = stoi(inputString);

			getline(appendFileToWorkWith, inputString);
		}
	}
	appendFileToWorkWith.close();
}

Hospital::~Hospital() {

}

void Hospital::addWardToList(bool fullNew) {
	HospitalInfo::WardList* buffList = new HospitalInfo::WardList[amountOfWards + 1];
	for (int i = 0; i < amountOfWards; i++) {
		buffList[i] = HospitalInfoData.wardList[i];
	}
	delete[] HospitalInfoData.wardList;
	HospitalInfoData.wardList = buffList;
	amountOfWards++;
	if (fullNew == true) {
		redactWardList(fullNew, amountOfWards - 1);
	}
	syncFiles();
}

void Hospital::removeWardFromList() {
	short idOfWard;
	do {
		for (int i = 0; i < amountOfWards; i++) {
			printf("\n%d. %s, (%d/%d)", i + 1, HospitalInfoData.wardList[i].nameOfWard.c_str(), HospitalInfoData.wardList[i].accessibleBunks, HospitalInfoData.wardList[i].amountOfBunks);
		}
		printf("\nВведіть номер палати, котру ви хочете видалити.\n0 якщо ви хочете вийти з цього меню.\n");
		cin >> idOfWard;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			idOfWard = -1;
		}
		if (idOfWard == 0) {
			return;
		}
		if (idOfWard <= 0 || idOfWard > amountOfWards) {
			system("cls");
			printf("\nТакого варіанту вибору не існує!\n");
		}
	} while (idOfWard <= 0 || idOfWard > amountOfWards);
	if (HospitalInfoData.wardList[idOfWard].accessibleBunks == HospitalInfoData.wardList[idOfWard].amountOfBunks) {
		HospitalInfo::WardList* buffList = new HospitalInfo::WardList[amountOfWards - 1];
		for (int i = 0; i < amountOfWards; i++) {
			if (i == idOfWard - 1) {
				for (int j = i + 1; j < amountOfWards; j++) {
					buffList[j-1] = HospitalInfoData.wardList[j];
					i = amountOfWards;
				}
			}
			else {
				buffList[i] = HospitalInfoData.wardList[i];
			}
		}
		delete[] HospitalInfoData.wardList;
		HospitalInfoData.wardList = buffList;
		amountOfWards--;
		syncFiles();
	}
	else {

		printf("\nЦя палата зайнята паціентами, спочатку переведіть їх у інші палати.\n");
	}
}

void Hospital::outListOfPatients() {
	bool exitCheck = false;
	short menuChoose;
	do {
	system("cls");
	for (int i = 0; i < amountOfPatients; i++) {
		printf("\n%d. %s",i+1, HospitalInfoData.ListOfPatients[i].patientsCardInfo.patientName.c_str());
	}
	printf("\nВведіть номер паціента, доступ к якому ви хочете получити.\n0 якщо хочете вийти з цього меню\n");
		cin >> menuChoose;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menuChoose = -1;
		}
		if (menuChoose == 0) {
			exitCheck = true;
		}
		else if (menuChoose > amountOfPatients || menuChoose < 0) {
			system("cls");
			printf("\nПацієнта під таким номером не існує!\n");
		}
		else {
			printf("\nВведіть 1 якщо ви хочете отримати доступ до картки пацієнта, 2 для доступу до історії хвороби пацієнта\n");
			short menuChoose2;
			cin >> menuChoose2;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				menuChoose2 = -1;
			}
			if (menuChoose2 == 1) {
			outListOfPatientsCards(menuChoose-1);
			}
			else if (menuChoose2 == 2) {
				outPatientsIllnesHistory(menuChoose - 1);
			}
			else if (menuChoose2 < 1 || menuChoose2 > 2) {
				system("cls");
				printf("\nВаріанта відповіді під таким номером не існує!\n");
			}
		}
	} while (exitCheck == false);
}

void Hospital::outListOfWards() {
	short menuChoose = 0;
	bool exitCheck = false;
	do {
		system("cls");
	printf("\nOut ListOfBunks\n");
	for (int i = 0; i < amountOfWards; i++) {
		printf("\n%d. %s\n	2.Кількість всіх ліжок: %d\n	Кількість доступних ліжок: %d", i + 1, HospitalInfoData.wardList[i].nameOfWard.c_str(), HospitalInfoData.wardList[i].amountOfBunks, HospitalInfoData.wardList[i].accessibleBunks);
	}
		printf("\nВведи номер палати, доступ до якої ви хочете отримати. 0 якщо ви хочете вийти з цього меню\n");
		cin >> menuChoose;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menuChoose = -1;
		}
		if (menuChoose == 0) {
			exitCheck = true;
		}
		else if (menuChoose > amountOfWards || menuChoose < 0) {
			system("cls");
			printf("\nПалати під таким номером не існує!\n");
		}
		else {
			redactWardList(false, menuChoose-1);
		}
	} while (exitCheck == false);
}

void Hospital::redactWardList(bool fullNew, short idOfWard) {
	string buffString;
	string buffStringChanged;
	int buffInt;
	short menuChoose = 0;
	bool exitMenu = false;
	system("cls");
	if (fullNew == false) { 
		do {
			printf("\n%d. %s\n	2.Кількість всіх ліжок: %d\n	Кількість доступних ліжок: %d\n", idOfWard + 1, HospitalInfoData.wardList[idOfWard].nameOfWard.c_str(), HospitalInfoData.wardList[idOfWard].amountOfBunks, HospitalInfoData.wardList[idOfWard].accessibleBunks);
			printf("Введи номер елементу в документі, який ви хочете змінити.\n 0 якщо ви хочете вийти з цього меню\n");
			menuChoose = -1;
			cin >> menuChoose;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				menuChoose = -1;
			}
			if (menuChoose == 0) {
				exitMenu = true;
			}
			else if (menuChoose > 2 || menuChoose < 0) {
				system("cls");
				printf("\nЕлементу під таким номером не існує!\n");
			}
			else {
				system("cls");
				switch (menuChoose) {
				case 1:
					printf("\nНазва палати: ");
					cin.ignore();
					getline(cin, buffStringChanged);
					for (int i = 0; i < amountOfPatients; i++) {
						if (strstr(HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.currentWard.c_str(), HospitalInfoData.wardList[idOfWard].nameOfWard.c_str()) != NULL) {
							HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.currentWard.erase(HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.currentWard.find(HospitalInfoData.wardList[idOfWard].nameOfWard), strlen(HospitalInfoData.wardList[idOfWard].nameOfWard.c_str()));
							HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.currentWard.append(buffStringChanged);
						}
					}
					HospitalInfoData.wardList[idOfWard].nameOfWard = buffStringChanged;
					break;
				case 2:
					printf("\n	Загальна кількість ліжок: ");
					do {
						cin >> buffInt;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							buffInt = -1;
							cout << "\nВи ввели неприпустимий символ" << endl;
						}
					} while (buffInt < 1 || (buffInt - HospitalInfoData.wardList[idOfWard].amountOfBunks) + HospitalInfoData.wardList[idOfWard].accessibleBunks < 0);
					HospitalInfoData.wardList[idOfWard].accessibleBunks = HospitalInfoData.wardList[idOfWard].accessibleBunks + (buffInt - HospitalInfoData.wardList[idOfWard].amountOfBunks);
					HospitalInfoData.wardList[idOfWard].amountOfBunks = buffInt;
					break;
				}

				printf("\nВи хочете змінити ще щось?\n1. Так\n2. Ні\n");
				do {
					cin >> menuChoose;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						menuChoose = -1;
					}
				} while (menuChoose < 1 || menuChoose > 2);
				if (menuChoose == 1) {

				}
				else if (menuChoose == 2) {
					exitMenu = true;
				}
			}
		} while (exitMenu == false);
	}
	else {
		printf("\nНазва палати: ");
		cin.ignore();
		getline(std::cin, HospitalInfoData.wardList[idOfWard].nameOfWard);

		printf("\n	Загальна кількість ліжок: ");
		do {
			cin >> buffInt;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				buffInt = -1;
				cout << "\nВи ввели неприпустимий символ" << endl;
			}
		} while (buffInt < 1);
		HospitalInfoData.wardList[idOfWard].accessibleBunks = buffInt;
		HospitalInfoData.wardList[idOfWard].amountOfBunks = buffInt;
	}
	syncFiles();
}

void Hospital::outListOfDoctors() {
	short menuChoose;
	bool exitCheck = false;
	do {
	system("cls");
	for (int i = 0; i < amountOfDoctors; i++) {
		printf("\n%d. %s, %s\n", i + 1, HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorInitials.c_str(), HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorProfession.c_str());
	}
		printf("\nВведіть номер лікаря, до даних якого ви хочете отримати доступ.\n 0 якщо ви хочете вийти з цього меню\n");
		cin >> menuChoose;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menuChoose = -1;
		}
		if (menuChoose == 0) {
			exitCheck = true;
		}
		else if (menuChoose > amountOfDoctors || menuChoose < 0) {
			system("cls");
			printf("\nЛікаря під таким номером не існує!\n");
		}
		else {
			redactDoctorList(false ,menuChoose - 1);
		}
	} while (exitCheck == false);
}

void Hospital::addDoctorToList(bool fullNew) {
	Doctor* buffList = new Doctor[amountOfDoctors + 1];
	for (int i = 0; i < amountOfDoctors; i++) {
		buffList[i] = HospitalInfoData.ListOfDoctors[i];
	}
	delete[] HospitalInfoData.ListOfDoctors;
	HospitalInfoData.ListOfDoctors = buffList;
	amountOfDoctors++;
	if (fullNew == true) {
		redactDoctorList(fullNew, amountOfDoctors - 1);
	}
	syncFiles();
}

void Hospital::removeDoctorFromList() {
	short idOfDoctor;
	string buffString;
	do {
		for (int i = 0; i < amountOfDoctors; i++) {
			printf("\n%d. %s\n	%s", i + 1, HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorInitials.c_str(), HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorProfession.c_str());
		}
		printf("\nВведіть номер лікаря, дані якого ви хочете видалити.\n 0 якщо ви хочете вийти з цього меню\n");
		cin >> idOfDoctor;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			idOfDoctor = -1;
		}
		if (idOfDoctor == 0) {
			return;
		}
		if (idOfDoctor <= 0 || idOfDoctor > amountOfDoctors) {
			system("cls");
			printf("\nТакого варіанту вибору не існує!\n");
		}
	} while (idOfDoctor <= 0 || idOfDoctor > amountOfDoctors);
	for (int i = 0; i < amountOfPatients; i++) {
		buffString = HospitalInfoData.ListOfDoctors[idOfDoctor-1].doctorsCredentials.doctorInitials + " " + HospitalInfoData.ListOfDoctors[idOfDoctor-1].doctorsCredentials.doctorProfession + "; ";
		if (strstr(HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.c_str(), buffString.c_str()) != NULL) {
			printf("\nУ пацієнта %s був видалений обранний лікар.\n", HospitalInfoData.ListOfPatients[i].patientsCardInfo.patientName.c_str());
			HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.erase(HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.find(buffString), strlen(buffString.c_str()));
		}
	}
		Doctor* buffList = new Doctor[amountOfDoctors - 1];
		for (int i = 0; i < amountOfDoctors; i++) {
			if (i == idOfDoctor - 1) {
				for (int j = i + 1; j < amountOfDoctors; j++) {
					buffList[j-1] = HospitalInfoData.ListOfDoctors[j];
					i = amountOfDoctors;
				}
			}
			else {
				buffList[i] = HospitalInfoData.ListOfDoctors[i];
			}
		}
		delete[] HospitalInfoData.ListOfDoctors;
		HospitalInfoData.ListOfDoctors = buffList;
		amountOfDoctors--;
		syncFiles();
}

void Hospital::redactDoctorList(bool fullNew, short idOfDoctor) {
	string buffString;
	string buffStringChanged;
	short menuChoose = 0;
	bool exitMenu = false;
	system("cls");
	if (fullNew == false) { 
		do {
			
			printf("\n1. %s,\n 2. %s\n", HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorInitials.c_str(), HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorProfession.c_str());
			printf("ВВедіть номер елементу в документі, котрий ви хочете змінита.\nВведіть 0 якщо ви хочете покинути це меню\n");
			menuChoose = -1;
			cin >> menuChoose;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				menuChoose = -1;
			}
			if (menuChoose == 0) {
				exitMenu = true;
			}
			else if (menuChoose > 2 || menuChoose < 0) {
				system("cls");
				printf("\nЕлементу під таким номером не існує!\n");
			}
			else {
				system("cls");
				switch (menuChoose) {
				case 1:
					printf("\nІм'я доктора:");
					cin.ignore();
					getline(cin, buffStringChanged);
					for (int i = 0; i < amountOfPatients; i++) {
						buffString = HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorInitials + " " + HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorProfession + "; ";
						if (strstr(HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.c_str(), buffString.c_str()) != NULL) {
							HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.erase(HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.find(buffString), strlen(buffString.c_str()));
							buffString = buffStringChanged + " " + HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorProfession + "; ";
							HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.append(buffString);
						}
					}
					HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorInitials = buffStringChanged;
					break;
				case 2:
					printf("\nСпеціальність лікаря: ");
					cin.ignore();
					getline(cin, buffStringChanged);
					for (int i = 0; i < amountOfPatients; i++) {
						buffString = HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorInitials + " " + HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorProfession + "; ";
						if (strstr(HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.c_str(), buffString.c_str()) != NULL) {
							HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.erase(HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.find(buffString), strlen(buffString.c_str()));
							buffString = HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorInitials + " " + buffStringChanged + "; ";
							HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors.append(buffString);
						}
					}
					HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorProfession = buffStringChanged;
					break;
				}
				printf("\nВи хочете змінити ще щось?\n1. Так\n2. Ні\n");
				do {
					cin >> menuChoose;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						menuChoose = -1;
					}
				} while (menuChoose < 1 || menuChoose > 2);
				if (menuChoose == 1) {

				}
				else if (menuChoose == 2) {
					exitMenu = true;
				}
			}
		} while (exitMenu == false);
	}
	else {
					printf("\nІм'я доктора:");
					cin.ignore();
					getline(std::cin, HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorInitials);

					printf("\nСпециальность доктора: ");
					getline(cin, HospitalInfoData.ListOfDoctors[idOfDoctor].doctorsCredentials.doctorProfession);
	}
	syncFiles();
}

void Hospital::outListOfPatientsCards(short idOfCard) {
	int menuChoose = 0;
	printf("\n============================================================"); //12
	printf("\n1.Ім'я пацієнта: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.patientName.c_str());
	printf("\n2.Стать паціента: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.sex.c_str());
	printf("\n3.День народження: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfBirth.c_str());
	printf("\n4.Номер телефону: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.phoneNumber.c_str());
	printf("\n5.Місце проживання: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.placeOfLiving.c_str());
	printf("\n6.Місце роботи та посада: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.placeOfWorkAndProfession.c_str());
	printf("\n7.Діспансерна група: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.DispensaryGroup.c_str());
	printf("\n8.Контінгенти: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.continget.c_str());
	printf("\n9.Інші пільгові категорії: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.otherBenefits.c_str());
	printf("\n10.Номер пільгового посвідчення: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.numberOfBenefitsDocument.c_str());
	printf("\n11.Узятий на облік: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfArival.c_str());
	printf("\n12.	Причина: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.reasonOfArival.c_str());
	printf("\n13.Знятий з обліку: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfDischarge.c_str());
	printf("\n14.	Причина: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.reasonOfDischarge.c_str());
	printf("\n============================================================\n"); //12
	do {
		printf("\nВведіть 1 якщо ви хочете відредагувати цю форму.\n 0 якщо ви хочете вийти з цього меню\n");
		cin >> menuChoose;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menuChoose = -1;
			cout << "\nВы ввели что-то кроме возможных вариантов" << endl;
		}
		if (menuChoose == 1) {
			redactPatientsCard(false, idOfCard);
			menuChoose = 0;
		}
	} while (menuChoose != 0);
}

void Hospital::outPatientsIllnesHistory(short idOfCard) {
	int menuChoose = 0;
	printf("\n============================================================"); //12
	printf("\n1. Хвороба: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.nameOfIllnes.c_str());
	printf("\n2. Історія хвороби: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.illnesDescription.c_str());
	printf("\n3. Приписанне лікування: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.prescribedTreatment.c_str());
	printf("\n4. Приписанна палата: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.c_str());
	printf("\n5. Прив'язанні лікарі: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.c_str());
	printf("\n============================================================\n"); //12 
	do {
		printf("\nВведіть 1 якщо ви хочете відредагувати цю форму.\n 0 якщо ви хочете вийти з цього меню\n"); 
		cin >> menuChoose;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menuChoose = -1;
			cout << "\nВи ввели щось окрім можливих варіантів" << endl;
		}
		if (menuChoose == 1) {
			redactPatientsIllnesHistory(idOfCard);
			menuChoose = 0;
		}
	} while (menuChoose != 0);
}

void Hospital::addPatientToList(bool fullNew) {
	Patient* buffList = new Patient[amountOfPatients + 1];
	for (int i = 0; i < amountOfPatients; i++) {
		buffList[i] = HospitalInfoData.ListOfPatients[i];
	}
	delete[] HospitalInfoData.ListOfPatients;
	HospitalInfoData.ListOfPatients = buffList;
	amountOfPatients++;
	if (fullNew == true) {
		redactPatientsCard(fullNew, amountOfPatients - 1);
	}
	syncFiles();
}

void Hospital::redactPatientsCard(bool newOrRedact, short idOfCard) {
	short menuChoose = 0;
	bool exitMenu = false;
	if (newOrRedact == false) { 
		do {
			system("cls");
			printf("\n============================================================"); //12
			printf("\n1.Ім'я пацієнта: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.patientName.c_str());
			printf("\n2.Стать паціента: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.sex.c_str());
			printf("\n3.День народження: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfBirth.c_str());
			printf("\n4.Номер телефону: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.phoneNumber.c_str());
			printf("\n5.Місце проживання: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.placeOfLiving.c_str());
			printf("\n6.Місце роботи та посада: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.placeOfWorkAndProfession.c_str());
			printf("\n7.Діспансерна група: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.DispensaryGroup.c_str());
			printf("\n8.Контінгенти: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.continget.c_str());
			printf("\n9.Інші пільгові категорії: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.otherBenefits.c_str());
			printf("\n10.Номер пільгового посвідчення: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.numberOfBenefitsDocument.c_str());
			printf("\n11.Узятий на облік: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfArival.c_str());
			printf("\n12.	Причина: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.reasonOfArival.c_str());
			printf("\n13.Знятий з обліку: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfDischarge.c_str());
			printf("\n14.	Причина: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.reasonOfDischarge.c_str());
			printf("\n============================================================\n");
			printf("Введіть номер елементу у документі, котрий ви хочете змінити\n0 якщо ви хочете вийти з цього меню\n");
			menuChoose = -1;
			cin >> menuChoose;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				menuChoose = -1;
			}
			if (menuChoose == 0) {
				exitMenu = true;
			}
			else if (menuChoose > 14 || menuChoose < 0) {
				printf("\nЕлементу під таким номером не існує!\n");
			}
			else {
				system("cls");
				switch (menuChoose) {
				case 1:
					printf("\nІм'я пацієнта: ");
					cin.ignore();
					getline(std::cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.patientName);
					break;
				case 2:
					printf("\nСтать паціента: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.sex);
					break;
				case 3: 
					printf("\nДень народження: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfBirth);
					break;
				case 4:
					printf("\nНомер телефону: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.phoneNumber);
					break;
				case 5:
					printf("\nМісце проживання: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.placeOfLiving);
					break;
				case 6:
					printf("\nМісце роботи та посада: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.placeOfWorkAndProfession);
					break;
				case 7:
					printf("\nДіспансерна група: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.DispensaryGroup);
					break;
				case 8:
					printf("\nКонтінгенти: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.continget);
					break;
				case 9:
					printf("\nІнші пільгові категорії: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.otherBenefits);
					break;
				case 10:
					printf("\nНомер пільгового посвідчення: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.numberOfBenefitsDocument);
					break;
				case 11:
					printf("\nУзятий на облік: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfArival);
					break;
				case 12:
					printf("\nПричина взяття на облік: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.reasonOfArival);
					break;
				case 13:
					printf("\nЗнятий з обліку: ");
cin.ignore();
getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfDischarge);
break;
				case 14:
					printf("\nПричина зняття з обліку: ");
					cin.ignore();
					getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.reasonOfDischarge);
					break;
				}
				printf("\nВи хочете змінити ще щось?\n1. Так\n2. Ні\n");
				do {
					cin >> menuChoose;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						menuChoose = -1;
					}
				} while (menuChoose < 1 || menuChoose > 2);
				if (menuChoose == 1) {

				}
				else if (menuChoose == 2) {
					exitMenu = true;
				}
			}
		} while (exitMenu == false);
	}
	else {
	printf("\nІм'я пацієнта:");
	cin.ignore();
	getline(std::cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.patientName);

	printf("\nСтать паціента: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.sex);

	printf("\nДень народження: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfBirth);

	printf("\nНомер телефону: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.phoneNumber);

	printf("\nМісце проживання: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.placeOfLiving);

	printf("\nМісце роботи та посада: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.placeOfWorkAndProfession);

	printf("\nДіспансерна група: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.DispensaryGroup);

	printf("\nКонтінгенти: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.continget);

	printf("\nІнші пільгові категорії: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.otherBenefits);

	printf("\nНомер пільгового посвідчення: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.numberOfBenefitsDocument);

	printf("\nУзятий на облік: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfArival);

	printf("\nПричина взяття на облік: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.reasonOfArival);

	printf("\nЗнятий з обліку: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfDischarge);

	printf("\nПричина зняття з обліку: ");
	getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.reasonOfDischarge);

	}
	syncFiles();
}

void Hospital::removePatientFromList() {
	short idOfPatient;
	do {
		for (int i = 0; i < amountOfPatients; i++) {
			printf("\n%d. %s", i + 1, HospitalInfoData.ListOfPatients[i].patientsCardInfo.patientName.c_str());
		}
		printf("\nВведіть номер паціенту, форму котрого, ви хочете видалити.\n 0 якщо хочете вийти з цього меню.\n");
		cin >> idOfPatient;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			idOfPatient = -1;
		}
		if (idOfPatient == 0) {
			return;
		}
		if (idOfPatient <= 0 || idOfPatient > amountOfPatients) {
			system("cls");
			printf("\nТакого варіанту вибору не існує!\n");
		}
	} while (idOfPatient <= 0 || idOfPatient > amountOfPatients);

	for (int i = 0; i < amountOfWards; i++) {
		if (strcmp(HospitalInfoData.ListOfPatients[idOfPatient-1].patientsIllnesHistory.currentWard.c_str(), HospitalInfoData.wardList[i].nameOfWard.c_str()) == 0) {
			HospitalInfoData.wardList[i].accessibleBunks++;
			i = amountOfWards;
		}
	}
	system("pause");
		Patient* buffList = new Patient[amountOfPatients - 1];
		for (int i = 0; i < amountOfPatients; i++) {
			if (i == idOfPatient - 1) {
				for (int j = i + 1; j < amountOfPatients; j++) {
					buffList[j-1] = HospitalInfoData.ListOfPatients[j];
					i = amountOfPatients;
				}
			}
			else {
				buffList[i] = HospitalInfoData.ListOfPatients[i];
			}
		}
		delete[] HospitalInfoData.ListOfPatients;
		HospitalInfoData.ListOfPatients = buffList;
		amountOfPatients--;
		syncFiles();
	}

void Hospital::redactPatientsIllnesHistory(short idOfCard) {
	int menuChoose;
	string buffString;
	bool exitMenu = false;
	do {
		system("cls");
		printf("\n============================================================");
		printf("\n1. Хвороба: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.nameOfIllnes.c_str());
		printf("\n2. Історія хвороби: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.illnesDescription.c_str());
		printf("\n3. Приписанне лікування: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.prescribedTreatment.c_str());
		printf("\n4. Приписанна палата: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.c_str());
		printf("\n5. Прив'язанні лікарі: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.c_str());
		printf("\n============================================================\n"); 
		printf("Введите номер элемента в документе, который вы хотели бы изменить.\n Введите 0 если вы хотите покинуть это меню.\n");
		menuChoose = -1;
		cin >> menuChoose;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menuChoose = -1;
		}
		if (menuChoose == 0) {
			break;
		}
		else if (menuChoose > 5 || menuChoose < 0) {
			printf("\nЕлементу під таким номером не існує!\n");
		}
		else {
			system("cls");
			switch (menuChoose) {
			case 1:
				printf("\nХвороба: ");
				cin.ignore();
				getline(std::cin, HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.nameOfIllnes);
				break;
			case 2:
				printf("\nІсторія хвороби: ");
				cin.ignore();
				getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.illnesDescription);
				break;
			case 3:
				printf("\nПриписанне лікування: ");
				cin.ignore();
				getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.prescribedTreatment);
				break;
			case 4:
				printf("\nПриписанна палата: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.c_str());
					printf("\nВведіть номер палати зі списку доступних палат, введіть 0 для выходу: ");
					for (int i = 0; i < amountOfWards; i++) {
						if (HospitalInfoData.wardList[i].accessibleBunks > 0) {
							if (strcmp(HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.c_str(), HospitalInfoData.wardList[i].nameOfWard.c_str()) != 0) {
								printf("\n%d. %s (%d/%d)\n", i + 1, HospitalInfoData.wardList[i].nameOfWard.c_str(), HospitalInfoData.wardList[i].accessibleBunks, HospitalInfoData.wardList[i].amountOfBunks);
							}
						}
					}

					do {
								cin >> menuChoose;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								menuChoose = -1;
								cout << "\nТакого варіанту вибору не існує!\n" << endl;
							}
							if (menuChoose == 0) {
								break;
							}
							if (HospitalInfoData.wardList[menuChoose - 1].accessibleBunks < 1) {
								menuChoose = -1;
							}
							if (menuChoose > 0 && amountOfWards >= menuChoose) {

									if (strcmp(HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.c_str(), HospitalInfoData.wardList[menuChoose - 1].nameOfWard.c_str()) != 0) {
										for (int i = 0; i < amountOfWards; i++) {
											if (strcmp(HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.c_str(), HospitalInfoData.wardList[i].nameOfWard.c_str()) == 0) {
												HospitalInfoData.wardList[i].accessibleBunks++;
												i = amountOfWards;
											}
										}
										HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.erase(HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.begin(), HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard.end());
										HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.currentWard = HospitalInfoData.wardList[menuChoose - 1].nameOfWard.c_str();
										HospitalInfoData.wardList[menuChoose - 1].accessibleBunks = HospitalInfoData.wardList[menuChoose - 1].accessibleBunks - 1;

										exitMenu = true;
									}
									else {
										printf("\nТакого варіанту вибору не існує!\n");
									}

								}
								else {
									printf("\nТакого варіанту вибору не існує!\n");
								}

							if (menuChoose == 0) {
								exitMenu == true;
								
							}
					} while (exitMenu != true);
					exitMenu = false;
				break;


			case 5:
				printf("\nПрікріпленні лікарі: %s", HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.c_str());
				printf("\nВведіть 1 якщо ви хочете прикрипити лікаря до паціента, 2 якщо ви хочете відкрипити лікаря: \n");
				do {
					cin >> menuChoose;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						menuChoose = -1;
					}
				} while (menuChoose < 1 || menuChoose > 2);
				if (menuChoose == 1) {
					printf("\nВведіть номер лікаря зі списку доступних лікарів: ");
					for (int i = 0; i < amountOfDoctors; i++) {
						printf("\n%d. %s\n	%s\n", i + 1, HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorInitials.c_str(), HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorProfession.c_str());
					}
					do {
						cin >> menuChoose;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							menuChoose = -1;
							cout << "\nТакого варіанту вибору не існує!\n" << endl;
						}
					} while (menuChoose < 0 || menuChoose > amountOfDoctors);
					buffString = HospitalInfoData.ListOfDoctors[menuChoose - 1].doctorsCredentials.doctorInitials + " " + HospitalInfoData.ListOfDoctors[menuChoose - 1].doctorsCredentials.doctorProfession + "; ";
					HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.append(buffString);
				}
				else if (menuChoose == 2) {
					if (HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.empty() == false) {
						printf("\nВведіть номер лікаря зі списку прикрепленних лікарів: ");
						for (int i = 0; i < amountOfDoctors; i++) {
							buffString = HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorInitials + " " + HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorProfession + "; ";
							if (strstr(HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.c_str(), buffString.c_str()) != NULL) {
								printf("\n%d. %s\n	%s\n", i + 1, HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorInitials.c_str(), HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorProfession.c_str());
							}
						}
						do {
							cin >> menuChoose;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								menuChoose = -1;
								cout << "\nТакого варіанту вибору не існує!\n" << endl;
							}
							if (menuChoose > 0 && menuChoose <= amountOfDoctors) {
								buffString = HospitalInfoData.ListOfDoctors[menuChoose - 1].doctorsCredentials.doctorInitials + " " + HospitalInfoData.ListOfDoctors[menuChoose - 1].doctorsCredentials.doctorProfession + "; ";
								if (strstr(HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.c_str(), buffString.c_str()) != NULL) {
									HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.erase(HospitalInfoData.ListOfPatients[idOfCard].patientsIllnesHistory.listOfAttachedDoctors.find(buffString), strlen(buffString.c_str()));
									exitMenu = true;
								}
								else {
									printf("\nТакого варіанту вибору не існує!\n");
								}

							}
							else {
								printf("\nТакого варіанту вибору не існує!\n");
							}
						} while (exitMenu != true);
						exitMenu = false;
					}
					else {
						printf("\nУ цього пацієнта нема прікріпленних лікарів!\n");
					}
				}
					else {
						printf("\nТакого варіанту вибору не існує!\n");
					}
				break;

			case 0:
				printf("\nПрив'язанні лікарі: ");
				cin.ignore();
				getline(cin, HospitalInfoData.ListOfPatients[idOfCard].patientsCardInfo.dateOfBirth);
				break;

			}
		}
			printf("\nВи хочете змінити ще щось?\n1. Так\n2. Ні\n");
			syncFiles();
			do {
				cin >> menuChoose;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					menuChoose = -1;

				}
			} while (menuChoose < 1 || menuChoose > 2);
				if (menuChoose == 1) {

				}
				else if (menuChoose == 2) {
					exitMenu = true;
				}
		} while (exitMenu == false);
		syncFiles();
}

void Hospital::GUI() {
	int menuChoose = -1;
	do {
		system("cls");
		//printf("\nPAT: %d\nDOC: %d\nBUN: %d", amountOfPatients, amountOfDoctors, amountOfWards);
		printf("\nЛаскаво просимо в систему обліку пацієнтів!\nБудь ласка, введіть номер необхідної операції:\n");
		printf("1. Виведення списку пацієнтів.\n");
		printf("2. Виведення списку лікарів.\n");
		printf("3. Виведення списку палат.\n");
		printf("4. Редагування списку пацієнтів\n");
		printf("5. Редагування списку лікарів\n");
		printf("6. Редагування списку палат\n");
		printf("0. Вихід з програми.\n");
		cin >> menuChoose;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menuChoose = -1;

		}
		if (menuChoose == 1) {
			outListOfPatients();
			system("cls");
		}
		else if (menuChoose == 2) {
			outListOfDoctors();
			system("cls");
;		}
		else if (menuChoose == 3) {
			outListOfWards();
			system("cls");
		}
		else if (menuChoose == 4) {
				do {
					printf("\nВведіть 1 якщо ви хочете додати пацієнта у список, 2 якщо ви хочете видалити пацієнта зі списку\n0 якщо ви хочете вийти з цього меню\n");
					cin >> menuChoose;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						menuChoose = -1;

					}
					if (menuChoose != 0) {
						if (menuChoose == 1) {
							do {
								printf("\nВведіть 1 якщо ви хочете створити шаблонну версію карти паціенту, введіть 2 якщо ви хочете ввести усі дані самостійно\n0 якщо ви хочете вийти з цього меню\n");
								cin >> menuChoose;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									menuChoose = -1;

								}
								if (menuChoose != 0) {
									if (menuChoose == 1) {
										addPatientToList(false);
									}
									else if (menuChoose == 2) {
										addPatientToList(true);
									}
								}
							} while (menuChoose > 2 || menuChoose < 0);
						}
						else if (menuChoose == 2) {
							if (amountOfPatients > 0) {
								removePatientFromList();
								system("cls");
							}
							else {
								system("cls");
								printf("\nНема зареєстрованний паціентів!\n");
							}
						}
						else {
							system("cls");
							printf("\nТакого варіанту вибору не існує!\n");
						}
					}
				} while (menuChoose > 2 || menuChoose < 0);
				menuChoose = -1;
		}
		else if (menuChoose == 5) {
			do {
				printf("\nВведіть 1 якщо ви хочете додати лікаря до списку, 2 якщо ви хочете видалити лікаря зі списку\n0 якщо ви хочете вийти з цього меню\n");
				cin >> menuChoose;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					menuChoose = -1;

				}
				if (menuChoose != 0) {
					if (menuChoose == 1) {
						do {
							printf("\nВведіть 1 якщо ви хочете створити шаблонну версію форми доктора, введіть 2 якщо ви хочете ввести усі початкові значення\n0 якщо ви хочете вийти з цього меню\n");
							cin >> menuChoose;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								menuChoose = -1;

							}
							if (menuChoose != 0) {
								if (menuChoose == 1) {
									addDoctorToList(false);
								}
								else if (menuChoose == 2) {
									addDoctorToList(true);
								}
							}
						} while (menuChoose > 2 || menuChoose < 0);
					}
					else if (menuChoose == 2) {
						if (amountOfDoctors > 0) {
							system("cls");
							removeDoctorFromList();
						}
						else {
							system("cls");
							printf("\nНема зареєстрованних лікарів!\n");
						}
					}
					else {
						system("cls");
						printf("\nТакого варіанту вибору не існує!\n");
					}
				}

			} while (menuChoose > 2 || menuChoose < 0);
			menuChoose = -1;
		}
		else if (menuChoose == 6) {
		do {
			printf("\nВведіть 1 якщо ви хочете додати палату в список, 2 якщо ви хочете видалити палату зі списку\n0 якщо ви хочете вийти з цього меню\n");
			cin >> menuChoose;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				menuChoose = -1;

			}
			if (menuChoose != 0) {
				if (menuChoose == 1) {
					do {
						printf("\nВведіть 1 якщо ви хочете створити шаблонну версію палати, введіть 2 якщо ви хочете ввести усі початкові значення\n0 якщо ви хочете вийти з цього меню\n");
						cin >> menuChoose;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							menuChoose = -1;

						}
						if (menuChoose != 0) {
							if (menuChoose == 1) {
								addWardToList(false);
							}
							else if (menuChoose == 2) {
								addWardToList(true);
							}
						}
					} while (menuChoose > 2 || menuChoose < 0);
				}
				else if (menuChoose == 2) {
					if (amountOfWards > 0) {
						system("cls");
						removeWardFromList();
					}
					else {
						system("cls");
						printf("\nНема зареєстрованних палат!\n");
					}
				}
				else {
					system("cls");
					printf("\nТакого варіанту вибору не існує!\n");
				}
			}
			} while (menuChoose > 2 || menuChoose < 0);
			menuChoose = -1;
		}

		else if (menuChoose == 0) {
			OnClosure();
			return;
		}
		else {
			system("cls");
			printf("\nТакого варіанту вибору не існує!\n");
		}
	} while (menuChoose != 0);
}

void Hospital::syncFiles() {
	string inputString;
	string generalVariablesFile = "GeneralVariablesFile.txt";
	string listOfPatientsCards = "listOfPatientsCards.txt";
	string listOfDoctors = "listOfDoctors.txt";
	string listOfWards = "listOfWards.txt";
	fstream appendFileToWorkWith;

	appendFileToWorkWith.open(generalVariablesFile, fstream::trunc | fstream::in | fstream::out);
	appendFileToWorkWith.seekg(0, ios::beg);
	appendFileToWorkWith << "Кількість пацієнтів у лікарні: " << amountOfPatients << "\n";
	appendFileToWorkWith << "Кількість лікарів у лікарні: " << amountOfDoctors << "\n";
	appendFileToWorkWith << "Кількість палат у лікарні: " << amountOfWards << "\n";
	appendFileToWorkWith.close();
	appendFileToWorkWith.open(listOfPatientsCards, fstream::trunc | fstream::in | fstream::out);
	appendFileToWorkWith.seekg(0, ios::beg);
	for (int i = 0; i < amountOfPatients; i++) {
		appendFileToWorkWith << "Ім'я пацієнта: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.patientName << "\n";
		appendFileToWorkWith << "Стать паціента: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.sex << "\n";
		appendFileToWorkWith << "День народження: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.dateOfBirth << "\n";
		appendFileToWorkWith << "Номер телефону: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.phoneNumber << "\n";
		appendFileToWorkWith << "Місце проживання: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.placeOfLiving << "\n";
		appendFileToWorkWith << "Місце роботи та посада: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.placeOfWorkAndProfession << "\n";
		appendFileToWorkWith << "Діспансерна група: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.DispensaryGroup << "\n";
		appendFileToWorkWith << "Контінгенти: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.continget << "\n";
		appendFileToWorkWith << "Інші пільгові категорії: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.otherBenefits << "\n";
		appendFileToWorkWith << "Номер пільгового посвідчення: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.numberOfBenefitsDocument << "\n";
		appendFileToWorkWith << "Узятий на облік: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.dateOfArival << "\n";
		appendFileToWorkWith << "Причина взяття на облік: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.reasonOfArival << "\n";
		appendFileToWorkWith << "Знятий з обліку: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.dateOfDischarge << "\n";
		appendFileToWorkWith << "Причина зняття з обліку: " << HospitalInfoData.ListOfPatients[i].patientsCardInfo.reasonOfDischarge << "\n";

		appendFileToWorkWith << "Хвороба: " << HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.nameOfIllnes << "\n";
		appendFileToWorkWith << "Історія хвороби: " << HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.illnesDescription << "\n";
		appendFileToWorkWith << "Приписанне лікування: " << HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.prescribedTreatment << "\n";
		appendFileToWorkWith << "Приписанна палата: " << HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.currentWard << "\n";
		appendFileToWorkWith << "Прив'язанні лікарі: " << HospitalInfoData.ListOfPatients[i].patientsIllnesHistory.listOfAttachedDoctors << "\n";

		appendFileToWorkWith << "////" << "\n";
	}
	appendFileToWorkWith.close();

	appendFileToWorkWith.open(listOfDoctors, fstream::trunc | fstream::in | fstream::out);
	appendFileToWorkWith.seekg(0, ios::beg);
	for (int i = 0; i < amountOfDoctors; i++) {
		appendFileToWorkWith << "Ім'я доктора:" << HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorInitials << "\n";
		appendFileToWorkWith << "Спеціальність: " << HospitalInfoData.ListOfDoctors[i].doctorsCredentials.doctorProfession << "\n";
		appendFileToWorkWith << "////" << "\n";
	}
	appendFileToWorkWith.close();

	appendFileToWorkWith.open(listOfWards, fstream::trunc | fstream::in | fstream::out);
	appendFileToWorkWith.seekg(0, ios::beg);
	for (int i = 0; i < amountOfWards; i++) {
		appendFileToWorkWith << "Назва палати: " << HospitalInfoData.wardList[i].nameOfWard << "\n";
		appendFileToWorkWith << "	Загальна кількість ліжок: " << HospitalInfoData.wardList[i].amountOfBunks << "\n";
		appendFileToWorkWith << "	Вільна кількість ліжок: " << HospitalInfoData.wardList[i].accessibleBunks << "\n";
		appendFileToWorkWith << "////" << "\n";
	}
	appendFileToWorkWith.close();
}

void Hospital::OnClosure() {
	printf("\nРобота програми завершується\n");
	printf("\nЗаписуємо дані...\n");
	syncFiles();
}

int main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	Hospital Hospital1;
	Hospital1.GUI();
}
