#pragma once
#include <iostream>
#include <mysql.h>
#include "ConexionBD.h"
#include <string>
using namespace std;
class Empleados
{
private:
	int idEmpleado = 0, idPuesto = 0;
	string nombres, apellidos, direccion, telefono, DPI, fecha_nacimiento, fecha_inicio_labores;
	bool genero = 0;
	//constructor	
public:
	Empleados() {
	};
	Empleados(int idE, string nom, string ape, string dir, string tel, string dpi, bool g, string fecha_n, int idP, string fecha_i_l) {
		idEmpleado = idE;
		nombres = nom;
		apellidos = ape;
		direccion = dir;
		telefono = tel;
		DPI = dpi;
		genero = g;
		fecha_nacimiento = fecha_n;
		idPuesto = idP;
		fecha_inicio_labores = fecha_i_l;
	}
	Empleados(int idP, string nom) {
		idPuesto = idP;
		nombres = nom;
	};
	Empleados(int idE) {
		idEmpleado = idE;
	};
	//metodos
	//set (modificar)
	void setidEmpleado(int id) { idEmpleado = id; };
	void setidPuesto(int idP) { idPuesto = idP; };
	void setNombres(string nom) { nombres = nom; };
	void setapellidos(string ape) { apellidos = ape; };
	void setdireccion(string dire) { direccion = dire; };
	void setTel(string tel) { telefono = tel; };
	void setDpi(string dpi) { DPI = dpi; };
	void setGenero(bool g) { genero = g; }
	void setfechanacimiento(string fecha) { fecha_nacimiento; };
	void setFecha_inicio_labores(string fecha) { fecha_inicio_labores = fecha; };
	//get (obtener)
	int getidE() { return idEmpleado; }
	int getidP() { return idPuesto; }
	string getNombres() { return nombres; }
	string getApe() { return apellidos; }
	string getdir() { return direccion; }
	string getTel() { return telefono; }
	string getDpi() { return DPI; }
	bool getGenero() { return genero; }
	string getfechanacimiento() { return fecha_nacimiento; }
	string getFecha_inicio_l() { return fecha_inicio_labores; }

	//CRUD
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string tt = to_string(idPuesto);
			int genero_int = genero ? 1 : 0;
			string insert = "INSERT INTO empleados(nombres,apellidos,direccion,telefono,DPI,genero,fecha_nacimiento,idPuesto,fecha_inicio_labores,fechaingreso) "
				"VALUES('" + nombres + "','" + apellidos + "','" + direccion + "','" + telefono + "','" + DPI + "'," + to_string(genero_int) + ",'" + fecha_nacimiento + "','" + tt + "','" + fecha_inicio_labores + "',  NOW()  )";
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
			string consulta = "SELECT e.idEmpleado, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, e.fecha_nacimiento, e.fecha_inicio_labores, e.fechaingreso, p.puesto, CASE WHEN e.genero = 0 THEN 'masculino' WHEN e.genero = 1 THEN 'femenino' END AS genero FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "idEmpleado: " << fila[0] << endl;
					cout << "Nombres: " << fila[1] << endl;
					cout << "Apellidos: " << fila[2] << endl;
					cout << "Direccion: " << fila[3] << endl;
					cout << "Telefono: " << fila[4] << endl;
					cout << "DPI: " << fila[5] << endl;
					cout << "Genero: " << fila[10] << endl;
					cout << "Fecha Nacimiento: " << fila[6] << endl;
					cout << "Fecha inicio Labores: " << fila[7] << endl;
					cout << "Fecha Ingreso: " << fila[8] << endl;
					cout << "Puesto :" << fila[9] << endl;
					cout << "\n";
				}
				cout << "\n";
				cout << "_________________________________" << endl;
			}
			else {
				system("cls");
				cout << "Query Select got problems " << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Error en la conexion" << endl;
		}
		cn.cerrar_conexion();

	};
	bool leerId() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(idPuesto);
			string consulta = "SELECT *FROM puestos  WHERE idPuesto = '" + t + "'";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				if (mysql_num_rows(resultado) == 0) {
					cout << "No se encontraron resultados con el idPuesto: " << t << endl;
					return false;
				}
				while (fila = mysql_fetch_row(resultado)) {
					cout << "idPuesto: " << fila[0] << endl;
					cout << "puesto: " << fila[1] << endl;
					cout << "\n";
				}
				cout << "\n";
				cout << "_________________________________" << endl;
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
	};
	void actualizar() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(idEmpleado);
			string tt = to_string(idPuesto);
			int genero_int = genero ? 1 : 0;
			string update = "UPDATE empleados SET nombres='" + nombres + "',apellidos='" + apellidos + "',direccion='" + direccion + "',telefono='" + telefono + "',DPI='" + DPI + "',genero=" + to_string(genero_int) + ",fecha_nacimiento='" + fecha_nacimiento + "',idPuesto=" + tt + ",fecha_inicio_labores='" + fecha_inicio_labores + "' WHERE idEmpleado = '" + t + "'";
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
			string deleteQuery = "DELETE FROM empleados WHERE idEmpleado = '" + to_string(idEmpleado) + "'";
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