#ifndef TANQUE_H
#define TANQUE_H
#include <cmath> // Biblioteca matematica
//Creación de espacio de nombres
namespace Estanques {
class Tanque { // Clase main Tanque
protected: // Atributos de la clase
    float volumen;
    int caudal;
public: // Metodos de la clase
    virtual float CalcularVolumen() const = 0;
    virtual float CalcularNivel(float volumen) const = 0;
    virtual void SetterPrametros(float param1, float param2, float param3) = 0;
    float get_volumen() const { return volumen; }
    void set_volumen(float vol) { volumen = vol; }
    int get_caudal() const { return caudal; }
    void set_caudal(float caud) {
        caudal = static_cast<int>(caud);
        if (caudal % 2 != 0) { caudal -= 1; }
    }
    virtual ~Tanque() {} // Destructor
};
class Prisma : public Tanque { // Clase hija Prisma
private: // Atributos de la clase
    float largo, ancho, alto;
public: // Metodos de la clase
    Prisma(float largo, float ancho, float alto) : largo(largo), ancho(ancho), alto(alto) {}
    float CalcularVolumen() const override { return largo * ancho * alto; }
    float CalcularNivel(float volumen) const override { return volumen / (largo * ancho); }
    void SetterPrametros(float alto, float ancho, float largo) override {
        this->largo = largo;
        this->alto = alto;
        this->ancho = ancho;
        volumen = CalcularVolumen();
    }
    float get_largo() const { return largo; }
    float get_ancho() const { return ancho; }
    float get_alto() const { return alto; }
};
class Cilindro : public Tanque { // Clase hija cilindro
private: // Atributos de la clase
    float radio, alto;
public: // Metodos de la clase
    Cilindro(float radio, float alto) : radio(radio), alto(alto) {}
    float CalcularVolumen() const override { return M_PI * std::pow(radio, 2) * alto; }
    void SetterPrametros(float alto, float radio, float = 0) override {
        this->alto = alto;
        this->radio = radio;
        volumen = CalcularVolumen();
    }
    float CalcularNivel(float volumen) const override { return volumen / (M_PI*radio * radio); }
    float get_radio() const { return radio; }
    float get_alto() const { return alto; }
};
class PIDController { // Clase asociada al controlador PID
public: // Metodo de la clase
    PIDController(float kp, float ki, float kd)
        : kp_(kp), ki_(ki), kd_(kd), prevError_(0), integral_(0) {}
    float calculate(float setpoint, float current, float dt, int caudal) {
        float error = setpoint - current;
        float P = kp_ * error;
        integral_ += error * dt;
        float I = ki_ * integral_;
        float D = kd_ * ((error - prevError_) / dt);
        float output = P + I + D;
        prevError_ = error;
        if (output > caudal) { output = caudal; }
        if (output < -caudal) { output = -caudal; }
        return output;}
private: // Atributos de la clase
    float kp_, ki_, kd_, prevError_, integral_;};
} // Cierre de namespace Estanques
#endif // TANQUE_H
