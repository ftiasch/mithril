import java.util.*;
import java.io.*;
import java.math.*;

class Equipment {
    int type, cost, price;
    ArrayList <String> dependency;

    Equipment(int type, int price) {
        this.type = type;
        this.cost = price;
        this.price = price;
        this.dependency = new ArrayList <String>();
    }

    void addDependency(String name) {
        this.dependency.add(name);
    }
}

class Pair {
    String name;
    int value;

    Pair(String name, int value) {
        this.name = name;
        this.value = value;
    }
}

public class Main implements Runnable {
    BufferedReader reader;

    Main() {
        reader = new BufferedReader(new InputStreamReader(System.in));
    }

    int nextInt() throws IOException {
        return Integer.parseInt(reader.readLine());
    }

    Pair parse(String line) {
        StringTokenizer tokenizer = new StringTokenizer(line);
        String name = tokenizer.nextToken();
        int value = Integer.parseInt(tokenizer.nextToken());
        return new Pair(name, value);
    }

    Set <String> solved;
    Map <String, Equipment> equipments;

    int getPrice(String name) {
        Equipment equipment = equipments.get(name);
        if (!solved.contains(name)) {
            for (String d : equipment.dependency) {
                equipment.price += getPrice(d);
            }
            solved.add(name);
        }
        return equipment.price;
    }

    public void run() {
        PrintWriter out = new PrintWriter(System.out);
        int testCount = 0;
        try {
            while (true) {
                testCount ++;
                equipments = new HashMap <String, Equipment>();
                for (int i = nextInt() - 1; i >= 0; -- i) {
                    Pair ret = parse(reader.readLine());
                    equipments.put(ret.name, new Equipment(0, ret.value));
                }
                for (int i = nextInt() - 1; i >= 0; -- i) {
                    String line = reader.readLine();
                    int seperator = line.indexOf(": ");
                    Pair ret = parse(line.substring(0, seperator));
                    Equipment equipment = new Equipment(1, ret.value);
                    line = line.substring(seperator + 2).replaceAll(", ", ",");
                    StringTokenizer tokenizer = new StringTokenizer(line, ",");
                    while (tokenizer.hasMoreTokens()) {
                        Pair ret2 = parse(tokenizer.nextToken());
                        for (int k = 0; k < ret2.value; ++ k) {
                            equipment.addDependency(ret2.name);
                        }
                    }
                    equipments.put(ret.name, equipment);
                }
                for (int i = nextInt() - 1; i >= 0; -- i) {
                    Pair ret = parse(reader.readLine());
                    equipments.put(ret.name, new Equipment(2, ret.value));
                }
                solved = new HashSet <String>();
                int money = 0;
                int occupy = 0;
                Map <String, Integer> count = new HashMap <String, Integer>();
                for (Map.Entry <String, Equipment> iter : equipments.entrySet()) {
                    count.put(iter.getKey(), 0);
                }
                for (int _ = nextInt() - 1; _ >= 0; -- _) {
                    String line = reader.readLine();
                    if (line.charAt(0) == '+') {
                        if (Character.isDigit(line.charAt(1))) {
                            money += Integer.parseInt(line.substring(1));
                        } else {
                            String name = line.substring(1);
                            if (equipments.containsKey(name)) {
                                Equipment equipment = equipments.get(name);
                                if (equipment.cost <= money) {
                                    if (equipment.type == 1) {
                                        Map <String, Integer> need = new HashMap <String, Integer>();
                                        for (String d : equipment.dependency) {
                                            if (need.containsKey(d)) {
                                                need.put(d, need.get(d) + 1);
                                            } else {
                                                need.put(d, 1);
                                            }
                                        }
                                        boolean valid = occupy + 1 - equipment.dependency.size() <= 6;
                                        for (Map.Entry <String, Integer> iter : need.entrySet()) {
                                            valid &= iter.getValue() <= count.get(iter.getKey());
                                        }
                                        if (valid) {
                                            occupy ++;
                                            money -= equipment.cost;
                                            count.put(name, count.get(name) + 1);
                                            for (String d : equipment.dependency) {
                                                occupy --;
                                                count.put(d, count.get(d) - 1);
                                            }
                                        }
                                    } else if (occupy < 6) {
                                        if (equipment.type == 0) {
                                            occupy ++;
                                            money -= equipment.cost;
                                            count.put(name, count.get(name) + 1);
                                        } else {
                                            if (count.get(name) == 0) {
                                                occupy ++;
                                            }
                                            money -= equipment.cost;
                                            count.put(name, count.get(name) + 1);
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        String name = line.substring(1);
                        if (equipments.containsKey(name)) {
                            Equipment equipment = equipments.get(name);
                            if (count.get(name) > 0) {
                                int delta = equipment.type == 2? count.get(name): 1;
                                occupy --;
                                money += delta * getPrice(name);
                                count.put(name, count.get(name) - delta);
                            }
                        }
                    }
                }
                out.println(String.format("Case %d:", testCount));
                out.println(money);
                out.println(occupy);
                ArrayList <String> result = new ArrayList <String>();
                for (Map.Entry <String, Integer> iter : count.entrySet()) {
                    String name = iter.getKey();
                    Equipment equipment = equipments.get(name);
                    if (iter.getValue() > 0) {
                        if (equipment.type == 2) {
                            result.add(String.format("%s: %d", name, iter.getValue()));
                        } else {
                            for (int k = iter.getValue(); k >= 1; -- k) {
                                result.add(String.format("%s: %d", name, 1));
                            }
                        }
                    }
                }
                Collections.sort(result);
                for (String s : result) {
                    out.println(s);
                }
                out.println();
                reader.readLine();
            }
        } catch (Exception e) {
        }
        out.close();
    }


    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}

