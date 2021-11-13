
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.ArrayList;

public class Solution {
    public static void main(String[] args) {
        int[] charCounts = new int[26];

        HashMap<String, Integer> map = new HashMap<>();

        try {
            BufferedReader input = new BufferedReader(new FileReader("words.txt"));
            
            String str = "";
            while((str = input.readLine()) != null) {
                if(str.length() > 1) {
                    for(int i = 0; i < str.length()-1; i++) {
                        charCounts[str.charAt(i)-'a']++;

                        String twoChars = "" + str.charAt(i) + str.charAt(i+1);
                        if(!map.containsKey(twoChars)) {
                            map.put(twoChars, 1);
                        }
                        else {
                            int value = map.get(twoChars);
                            value++;
                            map.put(twoChars, value);
                        }
                    }
                }
                charCounts[str.charAt(str.length()-1)-'a']++;
            }
        } catch(Exception e) {
            System.err.println("Error opening file: " + e);
        }

        for(int i = 0; i < 26; i++) {
            char c = (char)('a' + i);
            System.out.println(c + ": " + charCounts[i]);
        }

        System.out.println();

        int curMax = 0;
        int maxIndex = 0;
        for(int i = 0; i < 26; i++) {
            for(int j = 0; j < 26; j++) {
                if(curMax < charCounts[j]) {
                    maxIndex = j;
                    curMax = charCounts[j];
                }
            }
            char c = (char)('a' + maxIndex);
            System.out.println(c + ": " + charCounts[maxIndex]);
            charCounts[maxIndex] = 0;
            curMax = 0;
        }

        System.out.println();

        ArrayList<Entry> values = new ArrayList<>();
        Entry<String, Integer> max = null;
        for(Entry<String, Integer> entry : map.entrySet()) {
            if(entry.getValue() > 40) {
                values.add(entry);
            }
        }
        for(int i = 0; i < values.size(); i++) {
            System.out.println(values.get(i).getKey());
        }


    }
}