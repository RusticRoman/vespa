package ai.vespa.schemals.index;

/**
 * StructInheritanceNode
 */
public class StructInheritanceNode {

    private Symbol structDefinitionSymbol;

    public StructInheritanceNode(Symbol structDefinitionSymbol) {
        this.structDefinitionSymbol = structDefinitionSymbol;
    }

	@Override
    public int hashCode() {
        return (structDefinitionSymbol.getFileURI() + ":" + structDefinitionSymbol.getLongIdentifier()).hashCode();
	}

    @Override
    public boolean equals(Object other) {
        if (!(other instanceof StructInheritanceNode)) return false;
        return this.hashCode() == other.hashCode();
    }

    @Override
    public String toString() {
        return structDefinitionSymbol.getLongIdentifier();
    }

    public Symbol getSymbol() {
        return structDefinitionSymbol;
    }
}
