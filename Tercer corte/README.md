# Proyecto Rastreador de Salud

Proyecto de Juan José Triviño, Juan Esteban Espinoza, Santiago Chacón.
Aplicación de escritorio en C++ y Qt para gestionar indicadores de salud.

## Estructura del Proyecto (Refactorizada)

El código se organiza en los siguientes módulos principales:

### 1. Modelos y Utilidades

- **`models.h`**: Define las estructuras de datos principales:
  - `User`: Usuario del sistema (id, username, password).
  - `HealthRecord`: Registro de salud (peso, presión, glucosa, fecha).
- **`utils.h` / `utils.cpp`**: Funciones auxiliares.
  - `calculateStats`: Calcula promedios de los registros visibles.
  - `exportToCSV`: Exporta los datos a un archivo Excel/CSV.

### 2. Base de Datos

- **`databasemanager.h` / `databasemanager.cpp`**:
  - Maneja la conexión con SQLite (`health_tracker.db`).
  - Funciones CRUD: `createUser`, `addHealthRecord`, `getRecordsByUserAndDateRange`.
  - **Nota**: El archivo se repara automáticamente si falta una tabla.

### 3. Interfaz Gráfica (UI)

- **`loginwindow`**:
  - Primera ventana que aparece.
  - Maneja Login y Registro.
  - Al validar usuario, abre `MainWindow` y se cierra.
- **`mainwindow`**:
  - Ventana principal con tabla de registros.
  - Filtros de fecha (por defecto muestra el último mes).
  - Botones para Guardar nuevo registro, Calcular estadísticas y Exportar.

### 4. Entrada

- **`main.cpp`**: Punto de entrada. Inicia la aplicación y muestra el Login.

---

## Flujo de la Aplicación

1. **Inicio**: Se ejecuta `main.cpp` -> Muestra `LoginWindow`.
2. **Autenticación**:
   - El usuario ingresa credenciales o se registra.
   - `DatabaseManager` verifica/crea el usuario en SQLite.
3. **Uso Principal**:
   - Se abre `MainWindow` con los datos del usuario.
   - **Visualización**: La tabla carga automáticamente registros del último mes.
   - **Gestión**: El usuario puede agregar peso/presión/glucosa.
   - **Análisis**: Botón "Calcular Estadísticas" muestra promedios en pantalla.
   - **Exportación**: Botón "Exportar" genera un `.csv`.
4. **Cierre**: Al "Cerrar Sesión", la app se reinicia al Login.

---

## Comandos Claves

### 1. Compilar (Desde la raíz del proyecto)

```bash
# Configurar el proyecto (crear carpeta build_agent)
cmake -S . -B build_agent

# Compilar el ejecutable
cmake --build build_agent
```

### 2. Ejecutar

```bash
./build_agent/RastreadorSalud
```

### 3. Git (Subir cambios)

```bash
git add .
git commit -m "Descripción de cambios"
git push
```
