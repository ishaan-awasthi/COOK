public class Classifier {
    public Classifier(){}

    public String classify(String line){
        line = line.toLowerCase();

        if(line.contains("serve")){
            return "print";
        }

        if(line.contains("measure")){
            return "int";
        }

        if(line.contains("prepare")){
            return "String";
        }

        if(line.contains("mix")){
            return "add";
        }

        if(line.contains("reduce")){
            return "subtract";
        }

        if(line.contains("fold")){
            return "multiply";
        }

        if(line.contains("divide")){
            return "divide";
        }

        if(line.contains("excess")){
            return "mod";
        }

        if(line.contains("if")){
            return "if";
        }

        if(line.contains("while")){
            return "while";
        }

        return "comment";
    }

}
