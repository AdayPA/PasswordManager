CREATE TABLE password (
    id SERIAL PRIMARY KEY,
    nombre_usuario VARCHAR(50) NOT NULL,
    cifrado_aes VARCHAR(256) NOT NULL,
    salt VARCHAR(50) NOT NULL,
    correo VARCHAR(100) NOT NULL,
    fecha_creacion TIMESTAMP DEFAULT current_timestamp,
    columna_vacia1 VARCHAR(100),
    columna_vacia2 VARCHAR(100),
    columna_vacia3 VARCHAR(100),
    columna_vacia4 VARCHAR(100)
);