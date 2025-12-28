#pragma once
#include "raylib.h"

class Hitbox {

private:
	Rectangle hbox;	//tamaño real de la colision
	Vector2 offset;	//alineamiento con el sprite - la hbox puede ser mas chico o mas grande que el sprite
	bool debug;	//para testear

public:

	//cnstructor
	Hitbox(float ancho, float alto, Vector2 offset = { 0,0 }, bool debug = false);
	Hitbox(); //constructor por defecto

	void Sincro(Vector2 posSprite); //mueve la hitbox con el sprite

	Rectangle Getbox() const;	//devuelve hbox actual

	Vector2 GetOffset() const { return offset; }	//devuelve el offset de la hitbox

	bool Intersectan(const Hitbox& objeto) const;	//es const por que solo devuelve informacion, no modifica

	//colisiones con hitbox de otro objeto - solo detectan si hubo colision y desde donde
	//no usado en este proyecto
	bool ColisionaArriba(const Hitbox& objeto) const;
	bool ColisionaAbajo(const Hitbox& objeto) const;
	bool ColisionaIzquierda(const Hitbox& objeto) const;
	bool ColisionaDerecha(const Hitbox& objeto) const;

	//auxiliares para saber desde que direccion fue la colision
	//no usado en este proyecto
	float left()   const { return hbox.x; }
	float right()  const { return hbox.x + hbox.width; }
	float top()    const { return hbox.y; }
	float bottom() const { return hbox.y + hbox.height; }

	//debug
	void Draw() const;
	void DebugOn(bool activo);
};