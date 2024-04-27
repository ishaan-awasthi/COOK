public class Classifier {
    public Classifier(){}

    public String classify(String line){
        // Defining COOK syntax and vocabulary
        
        try {
            line = line.toLowerCase();
            if(line.contains("until")){return("until");}
            if(line.contains("if")){return("conditional");}
            if(line.contains("find how much of the")){return "input";}
            if(line.contains("find what brand of the")){return "input";}
            if(line.contains("serve")){return "print";}
            if(line.contains("measure")){return "int";}
            if(line.contains("prepare")){return "String";}
            if(line.contains("mix")){return "add";}
            if(line.contains("reduce")){return "subtract";}
            if(line.contains("fold")){return "multiply";}
            if(line.contains("divide")){return "divide";}
            if(line.contains("excess")){return "mod";}
            return "comment";
        } catch (Exception e) {
            throw new Error("\n\nError: Unknown exception occurred during classification!\n" + e.getMessage());
        }
    }
}
