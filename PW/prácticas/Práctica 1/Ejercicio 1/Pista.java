import java.util.ArrayList;
import java.util.List;

public class Pista {
    // Atributos
    private String nombre;
    private boolean disponible;
    private boolean esExterior;  // True si es exterior, false si es interior
    private TamanoPista tamano;
    private int maxJugadores;
    private List<Material> materiales;

    // Enumeración
    public enum TamanoPista { MINIBASKET, ADULTOS, VS3 }

    // Constructor vacío
    public Pista() {
        this.materiales = new ArrayList<>();
    }

    // Constructor parametrizado
    public Pista(String nombre, boolean disponible, boolean esExterior, TamanoPista tamano, int maxJugadores) {
        this.nombre = nombre;
        this.disponible = disponible;
        this.esExterior = esExterior;
        this.tamano = tamano;
        this.maxJugadores = maxJugadores;
        this.materiales = new ArrayList<>();
    }

    // Getters y Setters
    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public boolean isDisponible() {
        return disponible;
    }

    public void setDisponible(boolean disponible) {
        this.disponible = disponible;
    }

    public boolean isEsExterior() {
        return esExterior;
    }

    public void setEsExterior(boolean esExterior) {
        this.esExterior = esExterior;
    }

    public TamanoPista getTamano() {
        return tamano;
    }

    public void setTamano(TamanoPista tamano) {
        this.tamano = tamano;
    }

    public int getMaxJugadores() {
        return maxJugadores;
    }

    public void setMaxJugadores(int maxJugadores) {
        this.maxJugadores = maxJugadores;
    }

    public List<Material> getMateriales() {
        return materiales;
    }

    // Método toString
    @Override
    public String toString() {
        return "Pista [nombre=" + nombre + ", disponible=" + disponible + ", esExterior=" + esExterior 
                + ", tamano=" + tamano + ", maxJugadores=" + maxJugadores + "]";
    }

    // Método para consultar materiales disponibles
    public List<Material> consultarMaterialesDisponibles() {
        List<Material> disponibles = new ArrayList<>();
        for (Material material : materiales) {
            if (material.getEstado() == Material.EstadoMaterial.DISPONIBLE) {
                disponibles.add(material);
            }
        }
        return disponibles;
    }

    // Método para asociar material a la pista
    public boolean asociarMaterial(Material material) {
        if (this.esExterior && !material.isUsoExterior()) {
            return false;  // No se puede asociar material de interior a una pista exterior
        }
        // Restricciones: máximo 12 pelotas, 2 canastas, 20 conos
        long pelotas = materiales.stream().filter(m -> m.getTipo() == Material.TipoMaterial.PELOTAS).count();
        long canastas = materiales.stream().filter(m -> m.getTipo() == Material.TipoMaterial.CANASTAS).count();
        long conos = materiales.stream().filter(m -> m.getTipo() == Material.TipoMaterial.CONOS).count();
        
        if (material.getTipo() == Material.TipoMaterial.PELOTAS && pelotas >= 12) return false;
        if (material.getTipo() == Material.TipoMaterial.CANASTAS && canastas >= 2) return false;
        if (material.getTipo() == Material.TipoMaterial.CONOS && conos >= 20) return false;

        materiales.add(material);
        return true;
    }
}
