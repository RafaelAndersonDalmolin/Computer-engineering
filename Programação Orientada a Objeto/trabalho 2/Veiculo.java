public abstract class Veiculo {
    private String id;
    private int distpercorrida;
    private int qtdrodas;
    private Roda rodas[] = new Roda[4];
	private final String cor = "Vermelho";

    public Veiculo(String id, int qtdrodas) {
        this.id = id;
        this.distpercorrida = 0;
        this.qtdrodas = qtdrodas;
        
        for(int i=0;i<qtdrodas; i++)
        {
            this.rodas[i] = new Roda();
        }   
    }  
	public Veiculo() {
 		 this.distpercorrida = 0;
		 this.qtdrodas = 0;
    }  
    
    public abstract void mover();
    public abstract void imprimirTrajetoria();

  	public String getCor(){
		return this.cor;
	}
    public void calibrar ()
    {
        for(int i=0;i<qtdrodas; i++)
        {
            this.rodas[i].setCalibragem();
        }
    }
    
    public void esvaziar ()
    {
        for(int i=0;i<qtdrodas; i++)
        {
            this.rodas[i].setEsvaziar();
        }
    }
    
    public boolean getCalibragem()
    {
        return this.rodas[0].getCalibragem();
    }
    
    public int getDistpercorrida() {
        return distpercorrida;
    }

    public void setDistpercorrida(int x) {
        this.distpercorrida+=x;
    }

    public String getId() {
        return id;
    }

    public String toString() {
        return getId();
    } 
}
