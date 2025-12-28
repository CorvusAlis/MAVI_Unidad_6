#include "Hitbox.h"

Hitbox::Hitbox(float ancho, float alto, Vector2 off, bool dbg)
    :offset(off),
    debug(dbg)
{
    hbox = { 0, 0, ancho, alto };
}

Hitbox::Hitbox()
    : offset({ 0,0 }), debug(false)
{
    hbox = { 0, 0, 0, 0 };
}

void Hitbox::Sincro(Vector2 posSprite)
{
    //toma la posicion del sprite y la sincroniza con la hbox
    //en el constructor, x e y se inician en 0,0 - ahora se le asignan los valores
    hbox.x = posSprite.x + offset.x;
    hbox.y = posSprite.y + offset.y;
}

Rectangle Hitbox::Getbox() const
{
    return hbox;
}

bool Hitbox::Intersectan(const Hitbox& objeto) const
{
    return CheckCollisionRecs(hbox, objeto.hbox);   //detecta la colision entre el objeto que tiene la hitbox, y la hitbox de otro objeto
}

//colisiones - no usadas en este proyecto

bool Hitbox::ColisionaArriba(const Hitbox& objeto) const {

    if (!Intersectan(objeto)) return false;

    const float margen = 5.0f;  // margen de tolerancia de colision

    return bottom() > objeto.top() &&
        top() < objeto.top() &&
        (bottom() - objeto.top()) < margen;
}

bool Hitbox::ColisionaAbajo(const Hitbox& objeto) const {

    if (!Intersectan(objeto)) return false;

    const float margen = 5.0f;

    return top() < objeto.bottom() &&
        bottom() > objeto.bottom() &&
        (objeto.bottom() - top()) < margen;
}

bool Hitbox::ColisionaIzquierda(const Hitbox& objeto) const {

    if (!Intersectan(objeto)) return false;

    const float margen = 5.0f;

    return right() > objeto.left() &&
        left() < objeto.left() &&
        (right() - objeto.left()) < margen;
}

bool Hitbox::ColisionaDerecha(const Hitbox& objeto) const {

    if (!Intersectan(objeto)) return false;

    const float margen = 5.0f;

    return left() < objeto.right() &&
        right() > objeto.right() &&
        (objeto.right() - left()) < margen;
}

//debug

void Hitbox::Draw() const
{
    if (debug)
    {
        DrawRectangleLines(hbox.x, hbox.y, hbox.width, hbox.height, RED);   //dibuja un rectangulo rojo para mostrar el area de la hbox
    }
}

void Hitbox::DebugOn(bool activo)
{
    debug = activo;
}