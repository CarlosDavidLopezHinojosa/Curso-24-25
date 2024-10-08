public class Material {
    // Atributos
    private int id;
    private TipoMaterial tipo;
    private boolean usoExterior;  // True si es para exterior, false para interior
    private EstadoMaterial estado;

    // Enumeraciones
    public enum TipoMaterial { PELOTAS, CANASTAS, CONOS }
    public enum EstadoMaterial { DISPONIBLE, RESERVADO, MAL_ESTADO }

    // Constructor vacío
    public Material() {
    }

    // Constructor parametrizado
    public Material(int id, TipoMaterial tipo, boolean usoExterior, EstadoMaterial estado) {
        this.id = id;
        this.tipo = tipo;
        this.usoExterior = usoExterior;
        this.estado = estado;
    }

    // Getters y Setters
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public TipoMaterial getTipo() {
        return tipo;
    }

    public void setTipo(TipoMaterial tipo) {
        this.tipo = tipo;
    }

    public boolean isUsoExterior() {
        return usoExterior;
    }

    public void setUsoExterior(boolean usoExterior) {
        this.usoExterior = usoExterior;
    }

    public EstadoMaterial getEstado() {
        return estado;
    }

    public void setEstado(EstadoMaterial estado) {
        this.estado = estado;
    }

    // Método toString
    @Override
    public String toString() {
        return "Material [id=" + id + ", tipo=" + tipo + ", usoExterior=" + usoExterior + ", estado=" + estado + "]";
    }
}
