#include <iostream>
#include <string>
#include <regex>
#include <mysql.h>
#include "Cliente.h"
#include "Puestos.h"
#include "Empleados.h"
#include "Proveedores.h"
#include "Marcas.h"
#include "Productos.h"
#include "ventas_detalle.h"
#include "Compras.h"
#include <random>

using namespace std;
bool validarNIT(const string& nit) {
    regex formato("^\\d{5}-\\d{3}-\\d{1}$");
    if (nit == "Consumidor Final" || nit == "C/F") {
        return true;
    }
    return regex_match(nit, formato);
}
void C_Clientes() {
    char opcion;
    do {
        string NIT, nombres, apellidos, telefono, correo_electronico;
        int idCliente = 0;
        bool genero;
        cin.ignore();
        cout << "Ingrese Sus nombres: ";
        getline(cin, nombres);
        cout << "Ingrese sus apellidos: ";
        getline(cin, apellidos);
        cout << "Ingrese el NIT en la forma debe ser 12345-123-1: ";
        getline(cin, NIT);
        while (!validarNIT(NIT)) {
            cout << "El NIT que ingreso no es valido." << endl;
            cout << "Ingrese otro NIT que sea valido: " << endl;
            getline(cin, NIT);
        }
        cout << "Ingrese el genero: (0 masculino. 1 femenino)" << endl;
        cin >> genero;
        cin.ignore();
        cout << "Ingrese su telefono: ";
        getline(cin, telefono);
        cout << "Ingrese el correo electronico: ";
        getline(cin, correo_electronico);
        Cliente c = Cliente(idCliente, nombres, apellidos, NIT, genero, telefono, correo_electronico);
        c.crear();
        cout << "Desea continuar con esta opcion? " << endl;
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');
};
void R_Clientes() {
    Cliente l = Cliente();
    l.leer();
};
void U_Clientes() {
    string NIT, nombres, apellidos, telefono, correo_electronico;
    int idCliente = 0;
    bool genero;
    cout << "Ingrese el idCliente que desea actualizar: " << endl;
    cin >> idCliente;
    cin.ignore();
    cout << "Ingrese nuevos Nombres: " << endl;
    getline(cin, nombres);
    cout << "Ingrese nuevos Apellidos: " << endl;
    getline(cin, apellidos);
    cout << "Ingrese nuevo nit: " << endl;
    getline(cin, NIT);
    cout << "Ingrese nuevo genero: (0 masculino. 1 femenino)" << endl;
    cin >> genero;
    cin.ignore();
    cout << "Ingrese nuevo telefono: " << endl;
    getline(cin, telefono);
    cout << "Ingrese nuevo correo electronico: " << endl;
    getline(cin, correo_electronico);
    Cliente x = Cliente(idCliente, nombres, apellidos, NIT, genero, telefono, correo_electronico);
    x.actualizar();

};
void D_Clientes() {
    int idCliente = 0;
    cout << "Ingrese el idCliente que desea eliminar:" << endl;
    cin >> idCliente;
    cin.ignore();
    Cliente d = Cliente(idCliente);
    d.eliminar();
};
//tabla Puestos
void C_Puestos() {
    int idPuesto = 0;
    string puesto;
    cout << "Ingrese el puesto: " << endl;
    getline(cin, puesto);
    Puestos c = Puestos(idPuesto, puesto);
    c.crear();
};
void R_Puestos() {
    Puestos l = Puestos();
    l.leer();
};
void U_Puestos() {
    int idPuesto = 0;
    string puesto;
    cout << "Ingrese el idPuesto que desea modificar: " << endl;
    cin >> idPuesto;
    cin.ignore();
    cout << "Ingrese el nuevo puesto: " << endl;
    getline(cin, puesto);
    Puestos U = Puestos(idPuesto, puesto);
    U.actualizar();
};
void D_Puestos() {
    int idPuesto = 0;
    cout << "Ingrese el idPuesto que desea eliminar: " << endl;
    cin >> idPuesto;
    cin.ignore();
    Puestos D = Puestos(idPuesto);
    D.eliminar();
};

//Table Empleados
void C_Empleados() {
    int idPuesto, idEmpleado = 0;
    string nombres, apellidos, direccion, telefono, Dpi, fechanacimiento, fecha_inicio_labores;
    bool genero = 0;
    bool valor = false;

    while (!valor) {
        cout << "Ingrese el idPuesto: ";
        cin >> idPuesto;
        cin.ignore();
        Empleados l = Empleados(idPuesto, nombres);
        valor = l.leerId();
    }

    cout << "Ingrese los nombres: ";
    getline(cin, nombres);
    cout << "Ingrese los apellidos: ";
    getline(cin, apellidos);
    cout << "Ingrese la direccion : ";
    getline(cin, direccion);
    cout << "Ingrese el telefono : ";
    getline(cin, telefono);
    cout << "Ingrese el DPI: ";
    getline(cin, Dpi);
    cout << "Ingrese genero (0. masculino 1. femenino): ";
    cin >> genero;
    cin.ignore();
    cout << "Ingrese la fecha de nacimiento: ";
    getline(cin, fechanacimiento);
    cout << "Ingrese la fecha en que inicio su labores: ";
    getline(cin, fecha_inicio_labores);
    Empleados c = Empleados(idEmpleado, nombres, apellidos, direccion, telefono, Dpi, genero, fechanacimiento, idPuesto, fecha_inicio_labores);
    c.crear();
};
void R_Empleados() {
    Empleados l = Empleados();
    l.leer();

};
void U_Empleados() {
    int idPuesto, idEmpleado;
    string nombres, apellidos, direccion, telefono, Dpi, fechanacimiento, fecha_inicio_labores;
    bool genero = 0;
    cout << "Ingrese el idEmpleado que quiere cambiar:";
    cin >> idEmpleado;
    cin.ignore();
    cout << "Ingrese los nuevos nombres: ";
    getline(cin, nombres);
    cout << "Ingrese los nuevos apellidos: ";
    getline(cin, apellidos);
    cout << "Ingrese la nueva direccion : ";
    getline(cin, direccion);
    cout << "Ingrese el nuevo telefono : ";
    getline(cin, telefono);
    cout << "Ingrese el nuevo DPI: ";
    getline(cin, Dpi);
    cout << "Ingrese el idPuesto: ";
    cin >> idPuesto;
    cin.ignore();
    cout << "Ingrese nuevo genero (0. masculino 1. femenino): ";
    cin >> genero;
    cin.ignore();
    cout << "Ingrese la nueva fecha de nacimiento: ";
    getline(cin, fechanacimiento);
    cout << "Ingrese la nueva fecha de inicio de labores: ";
    getline(cin, fecha_inicio_labores);
    Empleados u = Empleados(idEmpleado, nombres, apellidos, direccion, telefono, Dpi, genero, fechanacimiento, idPuesto, fecha_inicio_labores);
    u.actualizar();
};
void D_Empleados() {
    int idEmpleado = 0;
    cout << "Ingrese el idEmpleado a eliminar: " << endl;
    cin >> idEmpleado;
    cin.ignore();
    Empleados D = Empleados(idEmpleado);
    D.eliminar();
};
//Table Marcas
void C_Marcas() {
    int idMarca = 0;
    string marca;
    cin.ignore();
    cout << "Ingrese la marca: " << endl;
    getline(cin, marca);
    Marcas C = Marcas(idMarca, marca);
    C.crear();
};
void R_Marcas() {
    Marcas l = Marcas();
    l.leer();
};
void U_Marcas() {
    int idMarca;
    string marca;
    cout << "Ingrese el idMarca que necesite: " << endl;
    cin >> idMarca;
    cin.ignore();
    cout << "Ingrese la nueva marca: " << endl;
    getline(cin, marca);
    Marcas U = Marcas(idMarca, marca);
    U.actualizar();
};
void D_Marcas() {
    int idMarca = 0;
    cout << "Ingrese el idMarca que desea eliminar: " << endl;
    cin >> idMarca;
    cin.ignore();
    Marcas D = Marcas(idMarca);
    D.eliminar();
}
//Table Productos
void C_Productos() {
    int idProducto = 0, idMarca = 0, existencia = 0;
    string producto, descripcion, imagen, fecha_ingreso;
    float precio_costo = 0, precio_venta = 0;

    bool valor = false;
    while (!valor) {
        cout << "Ingrese el idMarca a comprobar si existe: " << endl;
        cin >> idMarca;
        cin.ignore();
        Productos l = Productos(idMarca, producto);
        valor = l.leerId();
    }
    cout << "Ingrese el producto: " << endl;
    getline(cin, producto);
    cout << "Ingrese la descripcion: " << endl;
    getline(cin, descripcion);
    cout << "Ingrese la imagen: " << endl;
    getline(cin, imagen);
    cout << "Ingrese el precio costo: " << endl;
    cin >> precio_costo;
    cin.ignore();
    cout << "Ingrese el precio venta: " << endl;
    cin >> precio_venta;
    cin.ignore();
    cout << "Ingrese la existencia: " << endl;
    cin >> existencia;
    cin.ignore();
    Productos C = Productos(idProducto, producto, idMarca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso);
    C.crear();
};
void R_Productos() {
    Productos l = Productos();
    l.leer();
};
void U_Productos() {
    int idProducto, idMarca, existencia;
    string producto, descripcion, imagen, fecha_ingreso;
    float precio_costo, precio_venta;

    cout << "Ingrese el idProducto que desea actualizar:";
    cin >> idProducto;
    cin.ignore();
    cout << "Ingrese nuevo Producto: ";
    getline(cin, producto);
    cout << "Ingrese nuevo idMarca: ";
    cin >> idMarca;
    cin.ignore();
    cout << "Ingrese nueva descripcion : ";
    getline(cin, descripcion);
    cout << "Ingrese nueva imagen : ";
    getline(cin, imagen);
    cout << "Ingrese precio_costo: ";
    cin >> precio_costo;
    cout << "Ingrese precio_venta: ";
    cin >> precio_venta;
    cout << "Ingrese nueva existencia: ";
    cin >> existencia;
    cin.ignore();

    Productos u = Productos(idProducto, producto, idMarca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso);
    u.actualizar();
};
void D_Productos() {
    int idProducto = 0;
    cout << "Ingrese el idProducto que desea eliminar: " << endl;
    cin >> idProducto;
    cin.ignore();
    Productos d = Productos(idProducto);
    d.eliminar();
};
//Table Proveedores
void C_Proveedores() {
    int idProveedore = 0;
    string proveedor, nit, direccion, telefono;
    cin.ignore();
    cout << "Ingrese Proveedor: ";
    getline(cin, proveedor);
    cout << "Ingrese NIT en la forma debe ser 12345-123-1: ";
    getline(cin, nit);
    while (!validarNIT(nit)) {
        cout << "El NIT ingresado no es valido." << endl;
        cout << "Ingrese otro NIT que si sea valido: " << endl;
        getline(cin, nit);
    }
    cout << "Ingrese Direccion: ";
    getline(cin, direccion);
    cout << "Ingrese telefono: ";
    getline(cin, telefono);

    Proveedores c = Proveedores(idProveedore, proveedor, nit, direccion, telefono);
    c.crear();
};
void R_Proveedores() {
    Proveedores r = Proveedores();
    r.leer();
};
void U_Proveedores() {
    int idProveedore;
    string proveedor, nit, direccion, telefono;

    cout << "Ingrese el idProveedor que desea actualizar: ";
    cin >> idProveedore;
    cin.ignore();
    cout << "Ingrese Nuevo Proveedor: ";
    getline(cin, proveedor);
    cout << "Ingrese Nuevo NIT: ";
    getline(cin, nit);
    cout << "Ingrese NuevaDireccion: ";
    getline(cin, direccion);
    cout << "Ingrese telefono: ";
    getline(cin, telefono);

    Proveedores u = Proveedores();
    u.actualizar();
};
void D_Proveedores() {
    int idProveedore = 0;
    cout << "Ingrese el idProveedor a eliminar:" << endl;
    cin >> idProveedore;
    cin.ignore();
    Proveedores d = Proveedores(idProveedore);
    d.eliminar();
};

void C_ventas_detalle() {
    int no_factura = 0;
    int idVenta = 0, idempleado = 0, idcliente = 0, idproducto = 0, idventa = 0, idventa_detalle = 0;
    char serie = 'A', opcion;
    string fechafactura, Nit, cantidad;
    float precio_unitario = 0;

    int valClientes = 0;
    while (valClientes == 0) {
        cin.ignore();
        cout << "Ingrese Nit la forma debe ser 12345-123-1: " << endl;
        getline(cin, Nit);
        while (!validarNIT(Nit)) {
            cout << "El NIT ingresado no es valido." << endl;
            cout << "Ingrese Nit la forma debe ser 12345-123-1: " << endl;
            getline(cin, Nit);
        }
        Ventas_detalle VC =Ventas_detalle(Nit);
        valClientes = VC.leerNitClientes();
        idcliente = VC.getidC();
        if (valClientes == 0) {
            cout << "Ese Nit no existe desea crear un registro con ese Nit? (s/n)" << endl;
            cin >> opcion;
            cin.ignore();
            if (opcion == 's' || opcion == 'S') {
                C_Clientes();
            }
        }
    }
    bool valEmpleados = false;
    while (!valEmpleados) {
        cout << "Ingrese idEmpleado: " << endl;
        cin >> idempleado;
        cin.ignore();
        Ventas_detalle VE = Ventas_detalle(idempleado, no_factura, serie);
        valEmpleados = VE.leerIdEmpleados();
    }

    float valProducto = 0;
    char opcionpro;
    do {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution < > dis(1, 1000);
        no_factura = dis(gen);
        while (valProducto == 0) {
            cout << "Ingrese idProducto: " << endl;
            cin >> idproducto;
            cin.ignore();
            Ventas_detalle VP = Ventas_detalle(idproducto, idventa, idventa_detalle, cantidad);
            valProducto = VP.leerIdProductos();
            precio_unitario = valProducto;
            if (valProducto) {
                cout << "Ingrese la cantidad: " << endl;
                getline(cin, cantidad);
            }
        }
        cout << "Desea ingresar otro producto? (S/n)" << endl;
        cout << "opcion: ";
        cin >> opcionpro;
        Ventas_detalle C = Ventas_detalle(idVenta, no_factura, serie, fechafactura, idcliente, idempleado, idventa_detalle, idVenta, idproducto, cantidad, precio_unitario);
        C.crear();
        valProducto = 0;
    } while (opcionpro == 's' || opcionpro == 'S');
};

void R_venta_detalle() {
    Ventas_detalle r = Ventas_detalle();
    r.leer();
};

void U_venta_detalle() {
    int idVenta = 0, no_factura = 0, idcliente = 0, idempleado = 0, idventa_detalle = 0, idproducto = 0, idventa = 0;
    char serie = ' ';
    string fechafactura, cantidad;
    float precio_unitario;

    cout << "Ingrese idVenta a modificar de la tabla Ventas: " << endl;
    cin >> idVenta;
    cin.ignore();
    cout << "Ingrese el nuevo numero de factura: " << endl;
    cin >> no_factura;
    cin.ignore();
    cout << "Ingrese el nuevo numero de serie: " << endl;
    cin >> serie;
    cin.ignore();
    cout << "Ingrese la nueva fecha de factura: " << endl;
    getline(cin, fechafactura);
    cout << "Ingrese el nuevo idcliente: " << endl;
    cin >> idcliente;
    cin.ignore();
    cout << "Ingrese el nuevo idempleado: " << endl;
    cin >> idempleado;
    cin.ignore();
    system("pause");
    system("cls");
    cout << "_Ahora necesitamos los datos de ventas detalle_" << endl;
    fflush(stdin);
    cout << "Ingrese el idventa_detalle a actualizar: " << endl;
    cin >> idventa_detalle;
    cin.ignore();
    cout << "Ingrese el nuevo idventa: " << endl;
    cin >> idventa;
    cin.ignore();
    cout << "Ingrese el nuevo idProducto: " << endl;
    cin >> idproducto;
    cin.ignore();
    cout << "Ingrese la nueva cantidad: " << endl;
    getline(cin, cantidad);
    cout << "Ingrese el nuevo precio unitario: " << endl;
    cin >> precio_unitario;
    cin.ignore();
    Ventas_detalle U = Ventas_detalle(idVenta, no_factura, serie, fechafactura, idcliente, idempleado, idventa_detalle, idventa, idproducto, cantidad, precio_unitario);
    U.actualizar();
};
void D_ventas_detalle() {
    int idVenta, idventa_detalle;
    cout << "Ingrese el idVenta a eliminar: " << endl;
    cin >> idVenta;
    cout << "Ingrese el idventa_detalle a eliminar: " << endl;
    cin >> idventa_detalle;
    Ventas_detalle D = Ventas_detalle(idVenta, idventa_detalle);
    D.eliminar();
};

void C_Compras() {
    char opcion;
    //Variables Compras
    int no_orden_compra = 0, idProveedor = 0;
    int id_compra_detalle = 0;
    string fecha_orden, Nit, cantidad;
    //Variables Compras detalle
    int idproducto = 0, idcompra = 0;
    float precio_costo_unitario = 0;
    int ValProveedor = 0;

    while (ValProveedor == 0) {
        cin.ignore();
        cout << "Ingrese Nit de Proveedor... el formato debe ser 12345-123-1: " << endl;
        getline(cin, Nit);
        while (!validarNIT(Nit)) {
            cout << "El NIT ingresado no es valido." << endl;
            cout << "Ingrese Nit el formato debe ser 12345-123-1: " << endl;
            getline(cin, Nit);
        }
        Compras VP = Compras(Nit);
        ValProveedor = VP.leeridProveedores();

        if (ValProveedor) {
            idProveedor = ValProveedor;
        }
        if (ValProveedor == 0) {
            cout << "Ese Nit no existe desea crear un registro con ese Nit? (s/n)" << endl;
            cin >> opcion;
            cin.ignore();
            if (opcion == 's' || opcion == 'S') {
                C_Proveedores();
            }
        }
    }

    float valProducto = 0;
    char opcionpro;
    do {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution < > dis(1, 1000);
        no_orden_compra = dis(gen);
        while (valProducto == 0) {
            cout << "Ingrese idProducto: " << endl;
            cin >> idproducto;
            cin.ignore();
            Compras VPROD = Compras(idcompra, idproducto, id_compra_detalle, cantidad);
            valProducto = VPROD.leerIdProductos();
            precio_costo_unitario = valProducto;
            if (valProducto) {
                cout << "Ingrese la cantidad: " << endl;
                getline(cin, cantidad);
            }
        }
        cout << "Desea ingresar otro producto? (s/n)" << endl;
        cout << "opcion: ";
        cin >> opcionpro;
        Compras C = Compras(idcompra, no_orden_compra, idProveedor, fecha_orden, id_compra_detalle, idcompra, idproducto, cantidad, precio_costo_unitario);
        C.crear();
        valProducto = 0;
    } while (opcionpro == 's' || opcionpro == 'S');
};

void R_Compras() {
    Compras r = Compras();
    r.leer();
};
void U_Compras() {
    int idCompra = 0, no_orden_compra = 0, idProveedor = 0;
    string fecha_orden, cantidad;
    int idproducto = 0, idcompra = 0, idcompra_detalle = 0;
    float precio_costo_unitario = 0;

    cout << "Ingrese idCompra a modificar de la tabla Compras: " << endl;
    cin >> idCompra;
    cin.ignore();
    cout << "Ingrese el nuevo numero de Orden de Compra: " << endl;
    cin >> no_orden_compra;
    cin.ignore();
    cout << "Ingrese el nuevo ID de Proveedor: " << endl;
    cin >> idProveedor;
    cin.ignore();
    cout << "Ingrese la nueva fecha de orden: " << endl;
    getline(cin, fecha_orden);
    cin.ignore();
    system("pause");
    system("cls");
    cout << "========== Por favor ingresar Datos de la tabla Compras-Detalle ===========" << endl;
    fflush(stdin);
    cout << "Ingrese el idcompra a actualizar: " << endl;
    cin >> idcompra_detalle;
    cin.ignore();
    cout << "Ingrese el nuevo idCompra: " << endl;
    cin >> idcompra;
    cin.ignore();
    cout << "Ingrese el nuevo Producto: " << endl;
    cin >> idproducto;
    cin.ignore();
    cout << "Ingrese la nueva cantidad: " << endl;
    cin >> cantidad;
    cin.ignore();
    cout << "Ingrese el nuevo precio de costo unitario: " << endl;
    cin >> precio_costo_unitario;
    cin.ignore();
    Compras U = Compras(idCompra, no_orden_compra, idProveedor, fecha_orden, idcompra_detalle, idcompra, idproducto, cantidad, precio_costo_unitario);
    U.actualizar();
};
void D_Compras() {
    int idCompra, idCompra_detalle;
    cout << "Ingrese el idCompra que desea eliminar: " << endl;
    cin >> idCompra;
    cout << "Ingrese el idCompra_detalle que desea eliminar: " << endl;
    cin >> idCompra_detalle;
    Compras D = Compras(idCompra, idCompra_detalle);
    D.eliminar();
};
int main() {
    char opc;
    int opcion = 0;
    do {
        system("cls");

        cout << "Por favor elija su opcion: " << endl;
        cout << "1. Clientes " << endl;
        cout << "2. Puestos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Marcas" << endl;
        cout << "5. Proveedores" << endl;
        cout << "6. Productos " << endl;
        cout << "7. Compras & Compras Detalle " << endl;
        cout << "8. Ventas & Ventas Detalle " << endl;
        cin >> opcion;
        switch (opcion) {
        case 1: //Clientes
            system("cls");
            int opcionclientes;
            cout << "___Bienvenido a Clientes___" << endl;
            cout << "1. Crear 2.Leer 3.Actualizar 4.Eliminar" << endl;
            cout << "opcion:";
            cin >> opcionclientes;
            switch (opcionclientes) {
            case 1:
                C_Clientes();
                break;
            case 2:
                R_Clientes();
                break;
            case 3:
                U_Clientes();
                break;
            case 4:
                D_Clientes();
                break;
            default: cout << "Esa opcion no existe!" << endl;
                break;
            }
            break;
        case 2: //Puestos
            system("cls");
            int opcionpuestos;
            cout << "___Bienvenido a Puestos___" << endl;
            cout << "1. Crear 2.Leer 3.Actualizar 4.Eliminar" << endl;
            cout << "opcion:";
            cin >> opcionpuestos;
            switch (opcionpuestos) {
            case 1:
                C_Puestos();
                break;
            case 2:
                R_Puestos();
                break;
            case 3:
                U_Puestos();
                break;
            case 4:
                D_Puestos();
                break;
            default: cout << "Esa opcion no existe!" << endl;
                break;
            }
            break;
        case 3: //Empleados
            system("cls");
            int opcionempleados;
            cout << "___Bienvenido a Empleados___" << endl;
            cout << "1. Crear 2.Leer 3.Actualizar 4.Eliminar" << endl;
            cout << "opcion:";
            cin >> opcionempleados;
            switch (opcionempleados) {
            case 1:
                C_Empleados();
                break;
            case 2:
                R_Empleados();
                break;
            case 3:
                U_Empleados();
                break;
            case 4:
                D_Empleados();
                break;
            default: cout << "Esa opcion no existe!" << endl;
                break;
            }
            break;
        case 4: //Marcas
            system("cls");
            int opcionmarcas;
            cout << "___Bienvenido a Marcas___" << endl;
            cout << "1. Crear 2.Leer 3.Actualizar 4.Eliminar" << endl;
            cout << "opcion:";
            cin >> opcionmarcas;
            switch (opcionmarcas) {
            case 1:
                C_Marcas();
                break;
            case 2:
                R_Marcas();
                break;
            case 3:
                U_Marcas();
                break;
            case 4:
                D_Marcas();
                break;
            default: cout << "Esa opcion no existe!" << endl;
                break;
            }
            break;
        case 5: //Proveedores
            system("cls");
            int opcionproveed;
            cout << "___Bienvenido a Proveedores___" << endl;
            cout << "1. Crear 2.Leer 3.Actualizar 4.Eliminar" << endl;
            cout << "opcion:";
            cin >> opcionproveed;
            switch (opcionproveed) {
            case 1:
                C_Proveedores();
                break;
            case 2:
                R_Proveedores();
                break;
            case 3:
                U_Proveedores();
                break;
            case 4:
                D_Proveedores();
                break;
            default: cout << "Esa opcion no existe!" << endl;
                break;
            }
            break;
        case 6: //Productos
            system("cls");
            int opcionpro;
            cout << "___Bienvenido a los Productos___" << endl;
            cout << "1. Crear 2.Leer 3.Actualizar 4.Eliminar" << endl;
            cout << "opcion:";
            cin >> opcionpro;
            switch (opcionpro) {
            case 1:
                C_Productos();
                break;
            case 2:
                R_Productos();
                break;
            case 3:
                U_Productos();
                break;
            case 4:
                D_Productos();
                break;
            default: cout << "Esa opcion no existe!" << endl;
                break;
            }
            break;
        case 7: //Compras
            system("cls");
            int opcioncompras;
            cout << "___Bienvenido a las Compras___" << endl;
            cout << "1. Crear 2.Leer 3.Actualizar 4.Eliminar" << endl;
            cout << "opcion:";
            cin >> opcioncompras;
            switch (opcioncompras) {
            case 1:
                C_Compras();
                break;
            case 2:
                R_Compras();
                break;
            case 3:
                U_Compras();
                break;
            case 4:
                D_Compras();
                break;
            default: cout << "Esa opcion no existe!" << endl;
                break;
            }
            break;
        case 8: //Ventas
            system("cls");
            int opcionv;
            cout << "___Bienvenido al Registro de  Ventas y Ventas Detalle!___" << endl;
            cout << "1. Crear 2.Leer 3.Actualizar 4.Eliminar" << endl;
            cout << "opcion:";
            cin >> opcionv;
            switch (opcionv) {
            case 1:
                system("cls");
                C_ventas_detalle();
                break;
            case 2:
                R_venta_detalle();
                break;
            case 3:
                U_venta_detalle();
                break;
            case 4:
                D_ventas_detalle();
                break;
            default:
                cout << "Esa opcion no existe!" << endl;
                break;
            }
            break;
        default:
            cout << "La opcion ingresada no es valida!" << endl;
            break;
        }
        cout << "Desea continuar? (s/n)";
        cin >> opc;
    } while (opc == 's' || opc == 'S');
    system("pause");
    return 0;
}

