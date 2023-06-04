#pragma once
#include <iostream>
#include <mysql.h>
#include "ConexionBD.h"
#include <string>
using namespace std;
class Cliente
{
private:
	int idCliente = 0;
	bool genero = 0;
	string nombres, apellidos, Nit, telefono, correo_electronico;
	//constructor
public:
	Cliente() {
	};
	Cliente(int id, string nom, string ape, string n, bool g, string phone, string correo) {
		idCliente = id;
		nombres = nom;
		apellidos = ape;
		Nit = n;
		genero = g;
		telefono = phone;
		correo_electronico = correo;
	};
	Cliente(int id) {
		idCliente = id;
	};
	Cliente(string n, int id) {
		Nit = n;
		idCliente = id;
	};
	//metodos
	//set (modificar)
	void setidCliente(int id) { idCliente = id; }
	void setNombres(string nom) { nombres = nom; }
	void setApellidos(string ape) { apellidos = ape; }
	void setNit(string n) { Nit = n; }
	void setGenero(bool g) { genero = g; }
	void setTelefono(string phone) { telefono = phone; }
	void setCorreo_electronico(string correo) { correo_electronico = correo; }
	//get (obtener)
	int getidCliente() { return idCliente; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getNit() { return Nit; }
	bool getGenero() { return genero; }
	string getTelefono() { return telefono; }
	string getCorreo_electronico() { return correo_electronico; }


	//CRUD
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			int genero_int = genero ? 1 : 0;
			string insert = "INSERT INTO clientes(nombres,apellidos,nit,genero,telefono,correo_electronico,fecha_ingreso) "
				"VALUES('" + nombres + "','" + apellidos + "','" + Nit + "'," + to_string(genero_int) + ",'" + telefono + "','" + correo_electronico + "', NOW())";
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
			string consulta = "SELECT idCliente, nombres, apellidos, nit, telefono, correo_electronico, fecha_ingreso FROM clientes";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "idCliente: " << fila[0] << endl;
					cout << "nombres: " << fila[1] << endl;
					cout << "apellidos: " << fila[2] << endl;
					cout << "nit: " << fila[3] << endl;
					cout << "genero: " << fila[7] << endl;
					cout << "telefono :" << fila[4] << endl;
					cout << "correo_electronico :" << fila[5] << endl;
					cout << "fecha_ingreso: " << fila[6] << endl;
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
	}
	void actualizar() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(idCliente);
			int genero_int = genero ? 1 : 0;
			string update = "UPDATE clientes SET nombres='" + nombres + "',apellidos='" + apellidos + "',NIT='" + Nit + "',genero=" + to_string(genero_int) + ",telefono='" + telefono + "',correo_electronico='" + correo_electronico + "' WHERE idCliente = '" + t + "'";
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
			string deleteQuery = "DELETE FROM clientes WHERE idCliente = '" + to_string(idCliente) + "'";
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
	bool NitCliente()
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "SELECT nombres,apellidos FROM clientes where Nit='" + Nit + "'";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " " << fila[1] << endl;
				}
				cout << "\n";
				cout << "_________________________________" << endl;
			}
			else {
				system("cls");
				cout << "Busqueda Nit got problems" << mysql_error(cn.getConectar()) << endl;
				return false;
			}

		}
		else {
			cout << "Error en la conexion" << endl;
			return false;
		}
		cn.cerrar_conexion();
	};
};

