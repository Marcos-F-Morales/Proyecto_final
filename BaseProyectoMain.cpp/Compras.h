#pragma once
#include <iostream>
#include <mysql.h>
#include "ConexionBD.h"
#include <string>

class Compras {
private:
    //Compras
    int idCompra = 0,
        no_orden_compra = 0,
        idproveedor = 0;
    string fecha_orden, cantidad, fechaingreso, nit;
    //Compras_Detalle
    int id_compra_detalle = 0,
        idcompra = 0,
        idproducto = 0;
    float precio_costo_unitario = 0;

public: //Constructores
    Compras() {};
    //compras Detalle
    Compras(int idC, int noc, int idProvee, string fo, int idcd, int idc, int idprodu, string cntd, float pcu) {
        idCompra = idC;
        no_orden_compra = noc;
        idproveedor = idProvee;
        fecha_orden = fo;
        id_compra_detalle = idcd;
        idcompra = idc;
        idproducto = idprodu;
        cantidad = cntd;
        precio_costo_unitario = pcu;
    };
    //Validaciones compras
    Compras(string n) {
        nit = n;
    };

    //--> Eliminar
    Compras(int idC, int idcd) {
        idcompra = idC;
        id_compra_detalle = idcd;
    };

    Compras(int idC, int idcd, int idp) {
        idcompra = idC;
        id_compra_detalle = idcd;
        idproveedor = idp;
    };

    //Validacion compras_Detalle 
    Compras(int idC, int idP, int idcd, string can) {
        idcompra = idC;
        idproducto = idP;
        cantidad = can;
        id_compra_detalle = idcd;
    };

    int getidP() { return idproveedor; }
    //set
    void setidproveedor(int idp) { idproveedor = idp; }
    void setidcompra(int c) { idcompra = c; }

    //CRUD
    void crear() {
        //compras
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string tt = to_string(idproveedor);
            string noc = to_string(no_orden_compra);
            string insert = "INSERT INTO compras(no_orden_compra,idproveedor,fecha_orden,fechaingreso) "
                "VALUES('" + noc + "','" + tt + "',  NOW(),  NOW()  )";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                system("cls");
                cout << "Query Insert Successfuly" << endl;
            }
            else {
                system("cls");
                cout << "Query Insert Compras got problems" << mysql_error(cn.getConectar()) << endl;
            }
        }
        else {
            cout << "Error al conectar" << endl;
        }
        bool valor = leerIdCompras();
        if (valor == false) {
            return;
        }
        system("pause");
        //Compras Detalle
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string aa = to_string(idcompra);
            string aaa = to_string(idproducto);
            string aaaa = to_string(precio_costo_unitario);
            string insert = "INSERT INTO compras_detalle(idcompra,idProducto,cantidad,precio_costo_unitario)"
                "VALUES('" + aa + "','" + aaa + "','" + cantidad + "','" + aaaa + "')";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                system("cls");
                cout << "Query Insert Successfuly" << endl;
            }
            else {
                system("cls");
                cout << "Query Insert Compras_Detalle got problems " << mysql_error(cn.getConectar()) << endl;
            }
        }
        else {
            cout << "Error al conectar" << endl;
        }
        cn.cerrar_conexion();
    };
    //Validaciones Compras
    int leeridProveedores() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string consulta = "SELECT idProveedor,proveedor FROM Proveedores  WHERE nit = '" + nit + "'";
            const char* x = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), x);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                if (mysql_num_rows(resultado) == 0) {
                    cout << "No se encontraron resultados con el nit: " << nit << endl;
                    return 0;
                }
                while (fila = mysql_fetch_row(resultado)) {
                    idproveedor = stoi(fila[0]);
                    cout << "id: " << fila[0] << endl;
                    cout << "Proveedor: " << fila[1] << endl;

                    cout << "\n";
                }
                cout << "\n";
                cout << "_____" << endl;
            }
            else {
                system("cls");
                cout << "Query Select got problems" << mysql_error(cn.getConectar()) << endl;
                return 0;
            }
        }
        else {
            cout << "Error en la conexion" << endl;
            return 0;
        }
        cn.cerrar_conexion();
        return idproveedor;
    };
    //Validacion Compras_Detalle
    float leerIdProductos() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string p_u;
            string t = to_string(idproducto);
            string consulta = "SELECT producto,precio_costo FROM productos  WHERE idProducto = '" + t + "'";
            const char* x = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), x);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                if (mysql_num_rows(resultado) == 0) {
                    cout << "No se encontraron resultados con el idProducto: " << t << endl;
                    return 0;
                }
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "Producto: " << fila[0] << endl;
                    p_u = fila[1];
                    precio_costo_unitario = stof(p_u);
                    cout << "\n";
                }
                cout << "\n";
                cout << "_____" << endl;
            }
            else {
                system("cls");
                cout << "Query Select got problems" << mysql_error(cn.getConectar()) << endl;
                return 0;
            }

        }
        else {
            cout << "Error en la conexion" << endl;
            return 0;
        }
        cn.cerrar_conexion();
        return precio_costo_unitario;
    };
    bool leerIdCompras() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string t = to_string(no_orden_compra);
            string consulta = "SELECT idcompra FROM compras  WHERE no_orden_compra = '" + t + "'";
            const char* x = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), x);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                if (mysql_num_rows(resultado) == 0) {
                    cout << "No se encontraron resultados con el no_orden_compra: " << t << endl;
                    return false;
                }
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "Id Compra: " << fila[0] << endl;
                    idcompra = stoi(fila[0]);
                    cout << "\n";
                }
                cout << "\n";
                cout << "_____" << endl;
            }
            else {
                system("cls");
                cout << "Query Select got problems" << mysql_error(cn.getConectar()) << endl;
                return false;
            }

        }
        else {
            cout << "Error en la conexion" << endl;
            return false;
        }
        cn.cerrar_conexion();
        return true;
    };
    //LEER 
    void leer() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConectar()) {
            //Tabla COMPRAS
            string consulta = "SELECT c.idcompra,c.no_orden_compra,c.fecha_orden,c.fechaingreso,p.idproveedore,p.proveedor,p.nit from compras c JOIN proveedores p ON c.idproveedor = p.idproveedore; ";
            const char* x = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), x);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "=========== Compras ===========" << endl;
                    cout << "idCompra: " << fila[0] << endl;
                    cout << "No. Orden Compra: " << fila[1] << endl;
                    cout << "Fecha Orden: " << fila[2] << endl;
                    cout << "Fecha Ingreso: " << fila[3] << endl;
                    cout << "=========== Proveedores =========== " << endl;
                    cout << "idProveedor: " << fila[4] << endl;
                    cout << "Proveedor: " << fila[5] << endl;
                    cout << "NIT: " << fila[6] << endl;
                    cout << "\n";
                }
                cout << "\n";
                cout << "===========================================" << endl;
                cout << "\n";
            }
            else {
                system("cls");
                cout << "Query Select got problems" << mysql_error(cn.getConectar()) << endl;
            }
            //Tabla compras_detalle
            string consulta2 = "SELECT cd.idcompra_detalle, cd.idcompra, cd.idproducto, cd.cantidad, cd.precio_costo_unitario,(cd.cantidad*cd.precio_costo_unitario) AS total, c.idcompra, c.no_orden_compra, p.idProducto, p.producto FROM compras_detalle cd JOIN compras c ON cd.idcompra = c.idcompra JOIN productos p ON cd.idproducto = p.idProducto;";
            const char* y = consulta2.c_str();
            q_estado = mysql_query(cn.getConectar(), y);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "=========== Compras Detalle ===========" << endl;
                    cout << "idCompra_detalle:  " << fila[0] << endl;
                    cout << "idCompra: " << fila[1] << endl;
                    cout << "Cantidad: " << fila[3] << endl;
                    cout << "Precio_Costo_unitario: " << fila[4] << endl;
                    cout << "TOTAL: " << fila[5] << endl;
                    cout << "=========== Compras ===========" << endl;
                    cout << "idCompra: " << fila[6] << endl;
                    cout << "No. Orden Compra: " << fila[7] << endl;
                    cout << "=========== Productos ===========" << endl;
                    cout << "idProducto: " << fila[8] << endl;
                    cout << "Producto: " << fila[9] << endl;
                    cout << "\n";
                }
                cout << "\n";
                cout << "_____" << endl;
            }
            else {
                system("cls");
                cout << "Query Select got problems" << mysql_error(cn.getConectar()) << endl;
            }

        }
        else {
            cout << "Error en la conexion" << endl;
        }

        cn.cerrar_conexion();

    };
    void actualizar() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        //Compras
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string t = to_string(idCompra);
            string tt = to_string(no_orden_compra);
            string ip = to_string(idproveedor);
            string update = "UPDATE compras SET no_orden_compra='" + tt + "',idproveedor='" + ip + "',fecha_orden='" + fecha_orden + "' WHERE idCompra = '" + t + "'";
            const char* u = update.c_str();
            q_estado = mysql_query(cn.getConectar(), u);
            if (!q_estado) {
                system("cls");
                cout << "Query Update Successfuly" << endl;
            }
            else {
                system("cls");
                cout << "Query Update Failed: " << mysql_error(cn.getConectar()) << endl;
                return;
            }
        }
        else {
            cout << "Error al conectar" << endl;
            return;
        }
        cn.cerrar_conexion();

        //Compras detalle
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string t = to_string(idcompra);
            string tt = to_string(idproducto);
            string pcu = to_string(precio_costo_unitario);
            string cd = to_string(id_compra_detalle);
            string update = "UPDATE compras_detalle SET idcompra='" + t + "',idProducto='" + tt + "',cantidad='" + cantidad + "',precio_costo_unitario='" + pcu + "' WHERE idcompra_detalle = '" + cd + "'";
            const char* u = update.c_str();
            q_estado = mysql_query(cn.getConectar(), u);
            if (!q_estado) {
                system("cls");
                cout << "Query Update Successfuly" << endl;
            }
            else {
                system("cls");
                cout << "Query Update Failed: " << mysql_error(cn.getConectar()) << endl;
            }
        }
        else {
            cout << "Error al conectar" << endl;
        }
        cn.cerrar_conexion();
    };

    void eliminar() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();

        if (cn.getConectar()) {
            // Eliminar registros de la tabla compras_detalle
            string deleteQueryDetalle = "DELETE FROM compras_detalle WHERE idcompra_detalle = '" + to_string(id_compra_detalle) + "'";
            const char* d_detalle = deleteQueryDetalle.c_str();
            q_estado = mysql_query(cn.getConectar(), d_detalle);

            if (!q_estado) {
                system("cls");
                cout << "Registros eliminados exitosamente de la tabla compras_detalle" << endl;
            }
            else {
                system("cls");
                cout << "Ocurrió un problema al eliminar los registros de la tabla compras_detalle: " << mysql_error(cn.getConectar()) << endl;
                cn.cerrar_conexion();
                return;
            }
            // Eliminar registros de la tabla compras
            string deleteQueryCompras = "DELETE FROM compras WHERE idcompra = '" + to_string(idcompra) + "'";
            const char* d_compras = deleteQueryCompras.c_str();
            q_estado = mysql_query(cn.getConectar(), d_compras);

            if (!q_estado) {
                system("cls");
                cout << "Registros eliminados exitosamente de la tabla compras" << endl;
            }
            else {
                system("cls");
                cout << "Ocurrió un problema al eliminar los registros de la tabla compras: " << mysql_error(cn.getConectar()) << endl;
            }
        }
        else {
            cout << "Error al conectar" << endl;
        }

        cn.cerrar_conexion();
    }
};