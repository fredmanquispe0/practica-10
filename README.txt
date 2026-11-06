=====================================================================
 UNIVERSIDAD NACIONAL DEL ALTIPLANO - PUNO
 SIS210 Algoritmos y Estructuras de Datos - 2026-II
 Practica Semana 10: Arboles AVL
 Docente : Dr. Aldo Hernan Zanabria Galvez
 Integrantes:
   1. Machaca Quispe, Elfer Jaime   (codigo 250112)
   2. Quispe Quispe, Hanz Fredman
   3. Tito Quispe, Gabriel
 Escuela : Ingenieria de Sistemas - Ciclo IV
 Fecha   : 06/11/2026
=====================================================================

CONTENIDO
---------
  avl.h          Nodo, altura, factor de balance, 4 rotaciones,
                 balancear, insertar_avl, buscar, minimo, eliminar_avl
  avl_main.cpp   Casos de prueba P1-P6 con assert
  avl_python.py  AVL en Python + tabla BST vs AVL (2B) + menu SIGA (Act. 3)
  README.txt     Este archivo

COMO COMPILAR Y EJECUTAR
------------------------
  C++ (Actividades 1 y 2A):
      g++ -std=c++17 -Wall -o avl avl_main.cpp
      ./avl                      (en Windows: avl.exe)

  Salida obtenida:
      [P1 OK] insercion_simple
      [P2 OK] caso_LR
      [P3 OK] insercion_ordenada_grande h=4
      [P4 OK] eliminar_hoja
      [P5 OK] eliminar_raiz_dos_hijos
      [P6 OK] eliminar_con_rebalanceo
      === Todos los casos P1-P6 pasaron ===

  Python (Actividades 2B y 3), Python 3.12 o superior:
      python avl_python.py
  Primero imprime la tabla comparativa y luego abre el menu SIGA-UNAP-AVL.

NOTA SOBRE EL CODIGO DE LA GUIA
-------------------------------
  En los tests de la guia los mensajes estaban entre comillas simples
  ('P1: ...'). En C++ eso es un literal de caracter multiple, no un
  texto: cout imprime un numero en lugar del mensaje. Se cambiaron a
  comillas dobles. No se cambio ninguna condicion de los assert.
  Tambien se quito la variable raiz_orig de P5 porque no se usaba.
  El codigo se mantuvo lo mas simple posible para poder explicarlo.

=====================================================================
 ACTIVIDAD 1 - PREGUNTAS DE ANALISIS
=====================================================================

P1-A. Insertar 10, 20, 30
  Ocurre 1 rotacion simple. Al insertar 30, el nodo 10 queda con
  fb = +2 y su hijo derecho 20 tiene fb = +1: es el caso RR, que se
  corrige con una rotacion a la izquierda sobre 10. La nueva raiz es
  20 y la altura es 2.
  (El comentario de la guia dice "LL", pero el caso real es RR; el
  propio mensaje del assert lo confirma: "tras RR rotation".)

P1-B. Insertar 30, 10, 20
  Ocurre 1 rotacion doble, es decir, 2 rotaciones simples. El nodo 30
  queda con fb = -2 y su hijo izquierdo 10 tiene fb = +1: es el caso
  LR. Primero se rota a la izquierda sobre 10 (queda como LL) y luego
  a la derecha sobre 30. La nueva raiz es 20 y la altura es 2.

P1-C. Altura maxima de un AVL con 15 nodos
  El AVL mas "flaco" de altura h tiene N(h) = N(h-1) + N(h-2) + 1
  nodos: N(1)=1, N(2)=2, N(3)=4, N(4)=7, N(5)=12, N(6)=20.
  Con 15 nodos se alcanza N(5)=12 pero no N(6)=20, asi que la
  altura maxima posible es 5. La minima es 4, porque un arbol
  perfecto de altura 4 tiene exactamente 2^4 - 1 = 15 nodos.
  P3 acepta h <= 4 porque al insertar 1..15 en orden las rotaciones
  RR van formando justamente ese arbol perfecto (raiz 8). Nuestro
  programa obtuvo h = 4.

=====================================================================
 ACTIVIDAD 2B - TABLA COMPARATIVA (altura del arbol)
=====================================================================

       n |  BST (ord) |  AVL (ord) |    Teorico |  BST (rnd) |  AVL (rnd)
-------------------------------------------------------------------------
     100 |        100 |          7 |          9 |         16 |          8
     500 |        500 |          9 |         12 |         20 |         11
    1000 |       1000 |         10 |         14 |         23 |         12
    5000 |       5000 |         13 |         17 |         30 |         15
   10000 |      10000 |         14 |         19 |         31 |         16

  Teorico = int(1.44 * log2(n+1)).
  Las columnas "rnd" cambian un poco en cada ejecucion porque las
  claves se mezclan al azar; las columnas "ord" siempre salen igual.

P2B-A. BST con insercion ordenada
  La altura es igual al numero de nodos (h = n). Cada clave nueva es
  mayor que todas las anteriores y se va siempre a la derecha, asi que
  el arbol se convierte en una lista enlazada. Buscar cuesta O(n).

P2B-B. AVL con n = 10 000 frente al limite teorico
  No lo supera. El limite es int(1.44 * log2(10001)) = int(19.13) = 19
  y el AVL obtuvo 14 (ordenado) y 16 (aleatorio), es decir, 5 y 3
  niveles por debajo. Ademas 14 es el minimo posible para 10 000
  nodos, porque log2(10001) = 13.29 y se redondea hacia arriba.

P2B-C. AVL aleatorio vs AVL ordenado
  En nuestras pruebas no salen exactamente iguales: el aleatorio queda
  1 o 2 niveles mas alto (16 vs 14 con n = 10 000). Lo que si es igual
  es el comportamiento: ambos crecen como log2(n) y ninguno pasa el
  limite teorico. Esto pasa porque el AVL no depende del orden de
  llegada: despues de cada insercion revisa el factor de balance y rota
  si es +-2. Con datos ordenados las rotaciones siempre son RR y dejan
  un arbol casi perfecto; con datos aleatorios el arbol tambien queda
  balanceado, pero con algo mas de "holgura" permitida (fb = -1 o +1),
  por eso puede tener uno o dos niveles extra. En cambio el BST simple
  pasa de 31 (aleatorio) a 10 000 (ordenado).

=====================================================================
 ACTIVIDAD 3 - SIGA-UNAP-AVL
=====================================================================
  - Carga 10 estudiantes de muestra al iniciar.
  - Opcion 1: matricula usando el codigo como clave del AVL. Si el
    codigo ya existe, muestra un aviso y no lo inserta.
  - Opcion 2: busca por codigo y muestra el tiempo en microsegundos.
  - Opcion 3: recorrido inorden (izq, raiz, der), que en un BST da los
    estudiantes ordenados por codigo.
  - Opcion 4: total, altura actual, altura teorica y eficiencia.
    Con 11 estudiantes: altura 4, teorica 5, ÓPTIMO.
