#ifndef __LENGTH_CONVERTER_H__
#define __LENGTH_CONVERTER_H__
#include <string>
#include <stdexcept>
#include <iostream>

#include <QObject>

class LengthConverter
{
protected:
    LengthConverter * successor = nullptr;
public:
    virtual ~LengthConverter()
    {
        if (successor != nullptr)
        {
            delete successor;
        }
    }
    virtual void addSuccessor(LengthConverter* successor_in)
    {
        if (successor == this)
        {
            throw std::runtime_error("Cannot self-assign successor");
        }
        if (successor != nullptr)
        {
            delete successor;
        }
        successor = successor_in;
    }

    virtual std::string convert(std::string km, std::string unit) = 0;
};

class KmToMile : public LengthConverter
{
private:
    static constexpr double MILES_PER_KILOMETER = 0.621371;
public:
    virtual std::string convert(std::string km, std::string unit)
    {
        double doubleKm = std::stod(km);
        if (unit == "Mile")
        {
            return std::to_string(doubleKm * MILES_PER_KILOMETER);
        }
        else if (successor != nullptr)
        {
            return successor->convert(km, unit);
        }
        else
        {
            throw std::runtime_error("ERROR: No successor to handle unit " + unit);
        }
    }
};

class KmToYard : public LengthConverter
{
private:
    static constexpr double YARDS_PER_KILOMETER = 1093.6133;
public:
    virtual std::string convert(std::string km, std::string unit)
    {
        double doubleKm = std::stod(km);
        if (unit == "Yard")
        {
            return std::to_string(doubleKm * YARDS_PER_KILOMETER);
        }
        else if (successor != nullptr)
        {
            return successor->convert(km, unit);
        }
        else
        {
            throw std::runtime_error("ERROR: No successor to handle unit " + unit);
        }
    }
};

class KmToFoot : public LengthConverter
{
private:
    static constexpr double FEET_PER_KILOMETER =  3280.8399;
public:
    virtual std::string convert(std::string km, std::string unit)
    {
        double doubleKm = std::stod(km);
        if (unit == "Foot")
        {
            return std::to_string(doubleKm * FEET_PER_KILOMETER);
        }
        else if (successor != nullptr)
        {
            return successor->convert(km, unit);
        }
        else
        {
            throw std::runtime_error("ERROR: No successor to handle unit " + unit);
        }
    }
};

// Wrapper class needed for Qt
class QConverter : public QObject
{
    Q_OBJECT
private:
    LengthConverter * mConverter;
public:
    explicit QConverter() : QObject()
    {
        // Instantiate converters in QConverter object
        LengthConverter * mileConverter = new KmToMile();
        LengthConverter * yardConverter = new KmToYard();
        LengthConverter * footConverter = new KmToFoot();

        yardConverter->addSuccessor(footConverter);
        mileConverter->addSuccessor(yardConverter);

        mConverter = mileConverter;
    }
    virtual ~QConverter()
    {
        std::cout << "deleting mConverter\n";
        delete mConverter;
        mConverter = nullptr;
    }
    Q_INVOKABLE QString convert(QString km, QString unit)
    {
        std::string kmStl = km.toStdString();
        std::string unitStl = unit.toStdString();
        std::string conversionResult = mConverter->convert(kmStl, unitStl);
        return QString::fromUtf8(conversionResult.c_str());
    }
};


#endif // __LENGTH_CONVERTER_H__
