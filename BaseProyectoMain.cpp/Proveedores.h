#pragma once
#include <iostream>
#include <mysql.h>
#include "ConexionBD.h"
#include <string>

class Proveedores
{

private:
	int idProveedor;
	string proveedor, nit, direccion, telefono;

public:
	Proveedores() {
	};
	Proveedores(int id, string prov, string n, string dir, string tel) {
		idProveedor = id;
		proveedor = prov;
		nit = n;
		direccion = dir;
		telefono = tel;
	};
	Proveedores(int id) {
		idProveedor = id;
	};
	//metodos
	//set
	void set_idProveedore(int id) { idProveedor = id; }
	void set_proveedor(string prov) { proveedor = prov; }
	void set_nit(string n) { proveedor = n; }
	void set_direccion(string dir) { proveedor = dir; }
	void set_telefono(string tel) { proveedor = tel; }
	//get
	int get_idProveedore() { return idProveedor; }
	string get_proveedor() { return proveedor; }
	string get_nit() { return nit; }
	string get_direccion() { return direccion; }
	string get_telefono() { return telefono; }

	//CRUD
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {

			string t = to_string(idProveedor);
			string insert = "INSERT INTO proveedores(idProveedor,proveedor,nit,direccion,telefono) "
				"VALUES('" + t + "','" + proveedor + "','" + nit + "','" + direccion + "','" + telefono + "')";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				system("cls");
				cout << "Query Insert Successfuly" << endl;
			}
			else {
				system("cls");
				cout << "Query Insert got problems" << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Error al conectar" << endl;
		}
		cn.cerrar_conexion();
	};

	void leer() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "SELECT *FROM proveedores";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "idProveedore " << fila[0] << endl;
					cout << "Proveedores: " << fila[1] << endl;
					cout << "NIT: " << fila[2] << endl;
					cout << "Direccion: " << fila[3] << endl;
					cout << "Telefono: " << fila[4] << endl;
					cout << "\n";
				}
				cout << "\n";
				cout << "_________________________________" << endl;
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
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(idProveedor);
			string update = "UPDATE proveedores SET proveedores='" + proveedor + "',NIT='" + nit + "',Direccion='" + direccion + "',telefono=" + telefono + "' WHERE idProveedore = '" + t + "'";
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
			string deleteQuery = "DELETE FROM proveedores WHERE idProveedore = '" + to_string(idProveedor) + "'";
			const char* d = deleteQuery.c_str();
			q_estado = mysql_query(cn.getConectar(), d);
			if (!q_estado) {
				system("cls");
				cout << "Query Delete Successfuly" << endl;
			}
			else {
				system("cls");
				cout << "Query Delete got problems";
			}
		}
		else {
			cout << "Error al conectar" << endl;
		}
		cn.cerrar_conexion();
	};

};