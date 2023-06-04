#pragma once
#include <iostream>
#include <mysql.h>
#include "ConexionBD.h"
#include <string>
class Ventas_detalle
{
private:
	//Variables Ventas
	int idVenta = 0, nofactura = 0, idcliente = 0, idempleado = 0;
	char serie;
	string fechafactura;
	//Variables Ventas_detalle
	int idventa_detalle = 0, idventa = 0, idproducto = 0;
	string cantidad;
	float precio_unitario = 0;
	string Nit;
public:
	//constructor
	Ventas_detalle() {

	};
	//ventas
	Ventas_detalle(int idV, int nof, char s, string fechaf, int idc, int ide, int idventa_d, int idv, int idp, string cant, float precio_u) {
		idVenta = idV;
		nofactura = nof;
		serie = s;
		fechafactura = fechaf;
		idcliente = idc;
		idempleado = ide;
		idventa_detalle = idventa_d;
		idventa = idv;
		idproducto = idp;
		cantidad = cant;
		precio_unitario = precio_u;
	};
	//constructor para validacion ventas
	Ventas_detalle(string n) {
		Nit = n;
	};
	Ventas_detalle(int idE, int no, char s) {
		idempleado = idE;
		nofactura = no;
		serie = s;
	}

	//constructor para validaciones ventas detalle
	Ventas_detalle(int idp, int idv, int idventad, string c) {
		idproducto = idp;
		idventa = idv;
		idventa_detalle = idventad;
		cantidad = c;

	};
	Ventas_detalle(int idv, int idp, int idventad, string c, float pu) {
		idventa = idp;
		idproducto = idp;
		idventa_detalle = idventad;
		cantidad = c;
		precio_unitario = pu;

	};
	//eliminar
	Ventas_detalle(int idV, int idVD) {
		idVenta = idV;
		idventa_detalle = idVD;
	};
	//get

	int getidC() { return idcliente; }
	//set
	void setidcliente(int c) { idcliente = c; }
	void setidventa(int v) { idventa = v; }
	//CRUD
	void crear() {
		//ventas
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConectar()) {
			string tt = to_string(nofactura);
			system("pause");
			string insert = "INSERT INTO ventas(nofactura, serie, fechafactura, idcliente, idempleado, fechaingreso) "
				"VALUES('" + tt + "', '" + serie + "', NOW(), '" + to_string(idcliente) + "', '" + to_string(idempleado) + "', NOW())";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				system("cls");
				cout << "Query Insert Successfuly" << endl;
			}
			else {
				system("cls");
				cout << "Query Insert Ventas got problems" << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Error al conectar" << endl;
		}
		bool valor = leerIdVentas();
		if (!valor) {
			return;
		}
		system("pause");
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(idventa);
			string tt = to_string(idproducto);
			string ttt = to_string(precio_unitario);
			string insert = "INSERT INTO ventas_detalle(idVenta,idProducto,cantidad,precio_unitario)"
				"VALUES('" + t + "','" + tt + "','" + cantidad + "','" + ttt + "')";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				system("cls");
				cout << "Query Insert Ventas Detalle Successfuly" << endl;
			}
			else {
				system("cls");
				cout << "Query Insert Ventas got problems " << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Error al conectar" << endl;
		}
		cn.cerrar_conexion();
	}

	//Validaciones Ventas
	int leerNitClientes() {
		int q_estado;
		int id = 0;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "SELECT idCliente,nombres,apellidos FROM clientes WHERE NIT = '" + Nit + "'";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				if (mysql_num_rows(resultado) == 0) {
					cout << "No se encontraron resultados con el Nit: " << Nit << endl;
					return 0;
				}
				while (fila = mysql_fetch_row(resultado)) {
					id = stoi(fila[0]);
					cout << "Nombres: " << fila[1] << endl;
					cout << "Apellidos: " << fila[2] << endl;
					cout << "\n";
				}
				cout << "\n";
				cout << "___________" << endl;
			}
			else {
				system("cls");
				cout << "Query Select got problems: " << mysql_error(cn.getConectar()) << endl;
				return 0;
			}
		}
		else {
			cout << "Error en la conexion" << endl;
			return 0;
		}
		cn.cerrar_conexion();
		idcliente = id;
		return idcliente;
	}

	bool leerIdEmpleados() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(idempleado);
			string consulta = "SELECT nombres, apellidos FROM empleados  WHERE idEmpleado = '" + t + "'";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				if (mysql_num_rows(resultado) == 0) {
					cout << "No se encontraron resultados con el idEmpleado: " << t << endl;
					return false;
				}
				while (fila = mysql_fetch_row(resultado)) {
					cout << "Nombres: " << fila[0] << endl;
					cout << "Apellidos: " << fila[1] << endl;
					cout << "\n";
				}
				cout << "\n";
				cout << "___________" << endl;
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

	//Validaciones Ventas_detalle
	float leerIdProductos() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string p_u;
			string t = to_string(idproducto);
			string consulta = "SELECT producto, precio_venta FROM productos  WHERE idProducto = '" + t + "'";
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
					precio_unitario = stof(p_u);
					cout << "\n";
				}
				cout << "\n";
				cout << "___________" << endl;
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
		return precio_unitario;
	};
	bool leerIdVentas() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(nofactura);
			string consulta = "SELECT idVenta FROM ventas WHERE nofactura = '" + t + "'";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				if (mysql_num_rows(resultado) == 0) {
					cout << "No se encontraron resultados con el numero de Factura: " << t << endl;
					return false;
				}
				while (fila = mysql_fetch_row(resultado)) {
					cout << "idVenta: " << fila[0] << endl;
					idventa = stoi(fila[0]);
					cout << "\n";

				}
				cout << "\n";
				cout << "___________" << endl;
			}
			else {
				system("cls");
				cout << "Query Select tuvo problemas: " << mysql_error(cn.getConectar()) << endl;
				return false;
			}
		}
		else {
			cout << "Error en la conexión" << endl;
			return false;
		}
		cn.cerrar_conexion();
		return true;
	}

	void leer() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			//Tabla Ventas
			string consulta = "SELECT v.idventa, CONCAT(v.nofactura, '-', v.serie) AS correlativo, v.fechafactura, v.fechaingreso, e.idempleado, e.nombres, e.apellidos, c.idCliente, c.nombres, c.apellidos FROM ventas v JOIN empleados e ON v.idempleado = e.idempleado JOIN clientes c ON v.idcliente = c.idCliente;";
			const char* x = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), x);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "idVenta: " << fila[0] << endl;
					cout << "Correlativo: " << fila[1] << endl;
					cout << "Fecha Factura: " << fila[2] << endl;
					cout << "Fecha Ingreso: " << fila[3] << endl;
					cout << "____Empleado____" << endl;
					cout << "idEmpleado: " << fila[4] << endl;
					cout << "Nombres: " << fila[5] << endl;
					cout << "Apellidos: " << fila[6] << endl;
					cout << "____Cliente____" << endl;
					cout << "idCliente: " << fila[7] << endl;
					cout << "Nombres: " << fila[8] << endl;
					cout << "Apellidos: " << fila[9] << endl;
					cout << "\n";
				}
				cout << "\n";
				cout << "___________" << endl;
			}
			else {
				system("cls");
				cout << "Query Select got problems" << mysql_error(cn.getConectar()) << endl;
			}
			system("pause");
			//Tabla ventas_detalle
			string consulta2 = "SELECT vd.idventa_detalle,vd.cantidad,vd.precio_unitario, (vd.cantidad * vd.precio_unitario) AS total, v.idVenta,v.nofactura,p.idProducto,p.producto from ventas_detalle vd JOIN ventas v ON vd.idVenta = v.idVenta JOIN productos p ON vd.idProducto = p.idProducto;";
			const char* y = consulta2.c_str();
			q_estado = mysql_query(cn.getConectar(), y);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "____Ventas____" << endl;
					cout << "idVenta: " << fila[4] << endl;
					cout << "Numero Factura: " << fila[5] << endl;
					cout << "____Productos____" << endl;
					cout << "idProducto: " << fila[6] << endl;
					cout << "Producto: " << fila[7] << endl;
					cout << "_____________Ventas Detalles____________" << endl;
					cout << "idVenta_detalle:  " << fila[0] << endl;
					cout << "Cantidad: " << fila[1] << endl;
					cout << "precio_unitario: " << fila[2] << endl;
					cout << "total: " << fila[3] << endl;
				}
				cout << "\n";
				cout << "___________" << endl;
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
			string t = to_string(idVenta);
			string tt = to_string(nofactura);
			string ic = to_string(idcliente);
			string ie = to_string(idempleado);
			string update = "UPDATE ventas SET nofactura='" + tt + "',serie='" + serie + "',idcliente='" + ic + "',idempleado='" + ie + "' WHERE idVenta = '" + t + "'";
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

		//ventas detalle
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string t = to_string(idventa);
			string tt = to_string(idproducto);
			string pu = to_string(precio_unitario);
			string vd = to_string(idventa_detalle);
			string update = "UPDATE ventas_detalle SET idVenta='" + t + "',idProducto='" + tt + "',cantidad='" + cantidad + "',precio_unitario='" + pu + "' WHERE idventa_detalle = '" + vd + "'";
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
	void eliminar()
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar())
		{
			// Eliminar registro de la tabla ventas_detalle
			string t = to_string(idventa_detalle);
			string deleteQuery = "DELETE FROM ventas_detalle WHERE idventa_detalle = " + t;
			const char* d = deleteQuery.c_str();
			q_estado = mysql_query(cn.getConectar(), d);
			if (!q_estado)
			{
				cout << "Registro eliminado de ventas_detalle" << endl;
			}
			else
			{
				cout << "Error al eliminar registro de ventas_detalle: " << mysql_error(cn.getConectar()) << endl;
			}

			// Eliminar registro de la tabla ventas
			t = to_string(idVenta);
			deleteQuery = "DELETE FROM ventas WHERE idVenta = " + t;
			d = deleteQuery.c_str();
			q_estado = mysql_query(cn.getConectar(), d);
			if (!q_estado)
			{
				cout << "Registro eliminado de ventas" << endl;
			}
			else
			{
				cout << "Error al eliminar registro de ventas: " << mysql_error(cn.getConectar()) << endl;
			}
		}
		else
		{
			cout << "Error al conectar" << endl;
		}
		cn.cerrar_conexion();
	}
};