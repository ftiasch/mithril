import java.util.*;
import java.io.*;
import java.math.*;

class Expr {
	int type;

	BigInteger num;
	String var;

	Expr lhs, rhs;

	final static int NUM = 0;
	final static int VAR = 1;
	final static int ADD = 2;
	final static int MUL = 3;

	static HashMap<String,Expr> variable = new HashMap<String,Expr>();

	Expr(String var) {
		this.type = VAR;
		this.var = var;
	}

	Expr(BigInteger num) {
		this.type = NUM;
		this.num = num;
	}

	Expr(Expr lhs, int type, Expr rhs) {
		this.lhs = lhs;
		this.type = type;
		this.rhs = rhs;
	}

	static void clearVariables() {
		variable.clear();
	}
	
	static void assignVariable(String var, Expr expr) {
		variable.put(var, expr);
	}

	static Expr getVariable(String var) {
		Expr ret = variable.get(var);
		if (ret == null) {
			ret = new Expr(var);
		}
		return ret;
	}

	static Expr getExpr(String s) {
		if (Character.isLetter(s.charAt(0))) {
			return getVariable(s);
		} else {
			return new Expr(new BigInteger(s));
		}
	}

	Expr simplify() {
		if (type == NUM || type == VAR) {
			return this;
		}
		Expr lhsS = lhs.simplify();
		Expr rhsS = rhs.simplify();
		ArrayList<Expr> terms = new ArrayList<Expr>();
		for (Expr expr : new Expr[]{rhsS, lhsS}) {
			for (Expr ptr = expr; ;) {
				if (ptr.type != type) {
					terms.add(ptr);
					break;
				} else {
					terms.add(ptr.rhs);
					ptr = ptr.lhs;
				}
			}
		}
		ArrayList<Expr> terms2 = new ArrayList<Expr>();
		BigInteger num = null;
		for (Expr term : terms) {
			if (term.type == NUM) {
				if (num == null) {
					num = term.num;
				} else if (type == ADD) {
					num = num.add(term.num);
				} else {
					num = num.multiply(term.num);
				}
			} else {
				terms2.add(term);
			}
		}
		terms = terms2;
		if (terms.size() == 0) {
			return new Expr(num);
		}
		if (num != null) {
			if (type == ADD) {
				terms.add(0, new Expr(num));
			} else {
				terms.add(new Expr(num));
			}
		}
		Expr ret = terms.get(terms.size() - 1);
		for (int i = terms.size() - 2; i >= 0; i--) {
			ret = new Expr(ret, type, terms.get(i));
		}
		return ret;
	}

	void print(StringBuffer sb, boolean flag) {
		if (flag) {
			sb.append('(');
		}
		if (type == NUM) {
			sb.append(num);
		} else if (type == VAR) {
			sb.append(var);
		} else if (type == ADD) {
			lhs.print(sb, false);
			sb.append('+');
			rhs.print(sb, rhs.type == ADD);
		} else if (type == MUL) {
			lhs.print(sb, lhs.type == ADD);
			sb.append('*');
			rhs.print(sb, rhs.type == ADD || rhs.type == MUL);
		} else {
			sb.append("ERROR");
		}
		if (flag) {
			sb.append(')');
		}
	}

	public String toString() {
		StringBuffer sb = new StringBuffer();
		print(sb, false);
		return sb.toString();
	}
}

public class Main implements Runnable {

	BufferedReader in = null;
	StringTokenizer st = null;

	public void run() {
		try {
			in = new BufferedReader(new InputStreamReader(System.in));
			st = new StringTokenizer("");
			int tests = nextInt();
			for (int cas = 1; cas <= tests; ++cas) {
				int n = nextInt();
				Expr.clearVariables();
				Expr last = null;
				for (int i = 0; i < n; i++) {
					String var = next();
					next();
					Expr lhs = Expr.getExpr(next());
					int oper = next().equals("+") ? Expr.ADD : Expr.MUL;
					Expr rhs = Expr.getExpr(next());
					last = new Expr(lhs, oper, rhs);
					Expr.assignVariable(var, last);
				}
				System.out.println("Expression " + cas + ": " + last);
				System.out.println("Simplification " + cas + ": " + last.simplify());
				System.out.println();
			}
		} catch (Exception ex) {
			ex.printStackTrace();
			System.exit(-1);
		}
	}

	String next() throws IOException {
		while (!st.hasMoreTokens()) {
			String line = in.readLine();
			if (line == null) {
				throw new IOException("EOF");
			}
			st = new StringTokenizer(line);
		}
		return st.nextToken();
	}

	int nextInt() throws IOException {
		return Integer.parseInt(next());
	}

	public static void main(String[] args) {
		new Thread(new Main()).start();
	}
}
