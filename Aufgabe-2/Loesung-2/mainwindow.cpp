#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"


Mainwindow::Mainwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    QString output;

    // Initialize Database beforehand
    Database::init(false, "");

    // Print user interface
    output = "Welcome to your movie database. What do you want do do?\n";
    output += "Please choose one of the following options and refer to the output for further instructions:\n";
    output += "(1) Show all movies in vector\n";
    output += "(2) Add a movie\n";
    output += "(3) Remove movie from a specific position in vector\n";
    output += "(4) Re-Sort movies\n";
    output += "(5) Print average viewtime\n";
    output += "(6) Print total viewtime\n";
    output += "(7) Play specific movie from its position in vector\n";
    output += "(8) Add random amount of random rewievs into vector\n";
    output += "(9) Save current sorted state into file\n";
    output += "(10) Quit programm";
    ui->instr->setPlainText(output);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}


int Mainwindow::get_number() {
    QString outputstr;
    outputstr = ui->output->toPlainText();
    outputstr += "\n Please enter a number!\n";
    ui->output->setPlainText(outputstr);

    size_t flag = 1;

    while (flag != std::string::npos)
    {
        std::string str;
        str = ui->input_0->text().toUtf8();
        flag = str.find_first_not_of("-0123456789");

        if (flag == std::string::npos)
            return stoi(str);
        outputstr += "Did not enter a valid number. Try again!\n";
        ui->output->setPlainText(outputstr);
    }
    return -1;
}

void Mainwindow::on_pushButton_0_clicked()
{
    QString outputstr;
    std::stringstream strstream;
    int i = ui->input_0->text().toInt();

    while (i < 1 || i > 10)
    {
        outputstr = QString("Please choose between the given options 1-10!");
        ui->output->setPlainText(outputstr);
    }


    // Process selection with given functions
    switch (i)
    {
        case 1:
            strstream = Database::printMovies();
            outputstr = QString::fromUtf8(strstream.str().c_str());
            ui->output->setPlainText(outputstr);
            break;

        case 2:
            ui->stackedWidget->setCurrentIndex(1);
            break;

        case 3:
            ui->stackedWidget->setCurrentIndex(2);
            break;

        case 4:
            strstream = Database::sortMovies();
            outputstr = QString::fromUtf8(strstream.str().c_str());
            ui->output->setPlainText(outputstr);
            break;

        case 5:
            strstream = Database::returnAvgViewTime();
            outputstr = QString::fromUtf8(strstream.str().c_str());
            ui->output->setPlainText(outputstr);
            break;

        case 6:
            strstream = Database::returnTotalViewTime();
            outputstr = QString::fromUtf8(strstream.str().c_str());
            ui->output->setPlainText(outputstr);
            break;

        case 7:
            ui->stackedWidget->setCurrentIndex(3);
            break;

        case 8:
            ui->stackedWidget->setCurrentIndex(4);
            break;

        case 9: {
            ui->stackedWidget->setCurrentIndex(5);
            break;
        }

        case 10:
            outputstr = QString("See you next time!");
            ui->output->setPlainText(outputstr);
            break;

        default:
            outputstr = QString("Error: Option not available!");
            ui->output->setPlainText(outputstr);
            break;
    }
    return;

}

void Mainwindow::on_pushButton_2_clicked()
{
    QString outputstr;
    std::stringstream strstream;
    std::string str;
    int i;
    int x = 1;
    std::string filename;

    i = Mainwindow::get_number();


    // Initialize nessecary case vars
    std::string mname;
    int mlength;
    int mrating;
    std::vector<int> mratings;
    std::string mgenre;

    std::cout << "Enter the name of the movie: ";
    getline(std::cin, mname);
    std::cout << std::endl;

    std::cout << "Enter the length of the movie in minutes: ";
    mlength = get_number();
    std::cout << std::endl;

    std::cout << "Enter ratings of the movie 1 - 5: ";
    mrating = get_number();
    while (mrating < 1 || mrating > 5) {
        std::cout << "Please enter a valid number: 1 - 5!" << std::endl;
        mrating = get_number();
    }
    mratings.push_back(mrating);

    while (x == 1)
    {
        std::cout << "Do you want to add another rating? Please choose one of the following options:" << std::endl
        << "(1) Yes" << std::endl
        << "(2) No" << std::endl;
        x = get_number();
        while (x < 0 || x > 2)
        {
            std::cout << "Please enter a valid number: 1 or 2!" << std::endl;
            x = get_number();
        }
        if (x == 1) {
            std::cout << "Enter ratings of the movie 1 - 5: ";
            mrating = get_number();
            while (mrating < 1 || mrating > 5) {
                std::cout << "Please enter a valid number: 1 - 5!" << std::endl;
                mrating = get_number();
            }
            mratings.push_back(mrating);
        }
    }
    std::cout << std::endl;

    std::cout << "Enter the genre of the movie: ";
    getline(std::cin, mgenre);
    std::cout << std::endl;

    Movie *m = new Movie(mname, mlength, mratings, mgenre);
    Database::addMovie(m);

    ui->stackedWidget->setCurrentIndex(0);
}


void Mainwindow::on_pushButton_3_clicked()
{
    QString outputstr;
    std::stringstream strstream;
    std::string str;
    int i;
    std::string filename;

    i = Mainwindow::get_number();

    if (Database::getMovieSize() > 0)
    {
        outputstr = "Enter the position of the movie in the Database to remove (counting starts at 0!):";
        ui->output->setPlainText(outputstr);

        i = Mainwindow::get_number();
        while (i < 1 || i > Database::getMovieSize() - 1)
        {
            outputstr = QString("Please enter a valid position from 0-");
            outputstr += QString::number(Database::getMovieSize() - 1);
            outputstr += QString(")!");
            ui->output->setPlainText(outputstr);
            i = Mainwindow::get_number();
        }

        strstream = Database::removeMovie(i);
        outputstr = QString::fromUtf8(strstream.str().c_str());
        ui->output->setPlainText(outputstr);
    }
    else
    {
        outputstr = QString("No movies left");
        ui->output->setPlainText(outputstr);
    }
}


void Mainwindow::on_pushButton_7_clicked()
{
    QString outputstr;
    std::stringstream strstream;
    std::string str;
    int i;
    std::string filename;

    if (Database::getMovieSize() > 0)
    {
        outputstr = "Enter the position of the movie in the Database to play (counting starts at 0!):";
        ui->output->setPlainText(outputstr);

        i = Mainwindow::get_number();
        while (i < 1 || i > Database::getMovieSize() - 1)
        {
            outputstr = QString("Please enter a valid position from 0-");
            outputstr += QString::number(Database::getMovieSize() - 1);
            outputstr += QString(")!");
            ui->output->setPlainText(outputstr);
            i = Mainwindow::get_number();
        }

        strstream = Database::playMovie(i);
        outputstr = QString::fromUtf8(strstream.str().c_str());
        ui->output->setPlainText(outputstr);
    }
    else
    {
        outputstr = QString("No movies left!");
        ui->output->setPlainText(outputstr);
    }
}

void Mainwindow::on_pushButton_8_clicked()
{
    QString outputstr;
    std::stringstream strstream;
    std::string str;
    int i;
    std::string filename;

    outputstr = QString("Please enter the amount of reviews you want to add!");
    ui->output->setPlainText(outputstr);

    i = Mainwindow::get_number();
    while (i < 1)
    {
        outputstr = "Please enter a valid position from 0-";
        outputstr += QString::number(Database::getMovieSize() - 1);
        outputstr += ")!";
        ui->output->setPlainText(outputstr);

        i = Mainwindow::get_number();
    }

    Database::simulateReviews(i);
    outputstr = "Reviews added!";
    ui->output->setPlainText(outputstr);

}

void Mainwindow::on_pushButton_9_clicked()
{

    QString outputstr;
    std::stringstream strstream;
    std::string str;
    int i;
    std::string filename;

    outputstr = QString("Please enter text-filename for the save: ");
    ui->output->setPlainText(outputstr);

    filename = ui->input_0->text().toUtf8();
    if (filename.find(".txt") == std::string::npos)
        filename += ".txt";
    Database::printMovies(filename);

}
