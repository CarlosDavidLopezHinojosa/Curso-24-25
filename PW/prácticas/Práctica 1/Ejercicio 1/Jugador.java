import java.util.Date;

public class Jugador {
    // Atributos
    private String nombre;
    private String apellidos;
    private Date fechaNacimiento;
    private Date fechaInscripcion;
    private String email;

    // Constructor vacío
    public Jugador() {
    }

    // Constructor parametrizado
    public Jugador(String nombre, String apellidos, Date fechaNacimiento, String email) {
        this.nombre = nombre;
        this.apellidos = apellidos;
        this.fechaNacimiento = fechaNacimiento;
        this.email = email;
        this.fechaInscripcion = new Date();  // Hora actual
    }

    // Getters y Setters
    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public String getApellidos() {
        return apellidos;
    }

    public void setApellidos(String apellidos) {
        this.apellidos = apellidos;
    }

    public Date getFechaNacimiento() {
        return fechaNacimiento;
    }

    public void setFechaNacimiento(Date fechaNacimiento) {
        this.fechaNacimiento = fechaNacimiento;
    }

    public Date getFechaInscripcion() {
        return fechaInscripcion;
    }

    public void setFechaInscripcion(Date fechaInscripcion) {
        this.fechaInscripcion = fechaInscripcion;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    // Método toString
    @Override
    public String toString() {
        return "Jugador [nombre=" + nombre + ", apellidos=" + apellidos + ", fechaNacimiento=" + fechaNacimiento 
                + ", fechaInscripcion=" + fechaInscripcion + ", email=" + email + "]";
    }

    // Método para calcular antigüedad
    public int calcularAntiguedad() {
        Date ahora = new Date();
        return ahora.getYear() - this.fechaInscripcion.getYear();
    }
}
