public class Lexer {
    public Lexer(){}

    public Object[] analyze(String line, String keyword) {
        line = line.toLowerCase();

        if(keyword.equals("print")){
            String sub = line.substring(line.indexOf("the")+4);
            String value = sub.substring(0, sub.indexOf(" "));
            return new Object[]{value};
        }

        if(keyword.equals("int")){
            String sub = line.substring(line.indexOf("of")+3);
            String varname = sub.substring(0, sub.indexOf(" "));
            Integer value = line.matches(".*\\d.*") ? Integer.parseInt(line.replaceAll("\\D", "")) : 0;
            return new Object[]{varname, value};
        }

        if(keyword.equals("String")){
            String sub = line.substring(line.indexOf("brand")+6);
            String varname = sub.substring(0, sub.indexOf(" "));
            String value = line.substring(line.indexOf("\"")+1, line.lastIndexOf("\""));

            return new Object[]{varname, value};
        }

        if(keyword.equals("add") || keyword.equals("subtract")){
            String sub = line.substring(line.indexOf("in the")+7);
            String populate = sub.substring(0, sub.indexOf(" "));
            sub = line.substring(line.indexOf(populate)+populate.length()+1);
            sub = sub.substring(sub.indexOf("the")+4);
            String first = sub.substring(0, sub.indexOf(" "));
            sub = line.substring(line.indexOf(populate)+populate.length()+1);
            sub = sub.substring(sub.indexOf(first)+first.length()+1);
            sub = sub.substring(sub.indexOf("the")+4);
            String second = sub.substring(0, sub.indexOf(" "));
            return new Object[]{populate, first, second};
        }

        if(keyword.equals("multiply") || keyword.equals("divide")){
            String sub = line.substring(line.indexOf("in the")+7);
            String populate = sub.substring(0, sub.indexOf(" "));
            sub = line.substring(line.indexOf(sub));
            sub = sub.substring(sub.indexOf("the")+4);
            String first = sub.substring(0, sub.indexOf(" "));
            sub = line.substring(line.indexOf("into the")+9);
            String second = sub.substring(0, sub.indexOf(" "));
            return new Object[]{populate, first, second};
        }

        if(keyword.equals("mod")){
            String sub = line.substring(line.indexOf("in the")+7);
            String populate = sub.substring(0, sub.indexOf(" "));
            sub = line.substring(line.indexOf(sub));
            sub = sub.substring(sub.indexOf("excess")+7);
            String first = sub.substring(0, sub.indexOf(" "));
            sub = line.substring(line.indexOf("into the")+9);
            String second = sub.substring(0, sub.indexOf(" "));
            return new Object[]{populate, first, second};
        }

        //conditionals, loops

        return new Object[]{};
    }
}
