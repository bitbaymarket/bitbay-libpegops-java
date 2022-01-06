package bay;

public class pegops {
   static {
      System.loadLibrary("pegops");
   }

   public static class Out_getpeglevel {
      public boolean out_ok;
      public String  out_peglevel_hex;
      public String  out_pegpool_pegdata64;
      public String  out_err;
   }
   public native Out_getpeglevel getpeglevel(
      int      inp_cycle_now,
      int      inp_cycle_prev,
      int      inp_peg_now,
      int      inp_peg_next,
      int      inp_peg_next_next,
      String   inp_exchange_pegdata64,
      String   inp_pegshift_pegdata64
   );

   public static class Out_updatepegbalances {
      public boolean out_ok;
      public String  out_balance_pegdata64;
      public long    out_balance_liquid;
      public long    out_balance_reserve;
      public String  out_pegpool_pegdata64;
      public String  out_err;
   }
   public native Out_updatepegbalances updatepegbalances(
      String   inp_balance_pegdata64,
      String   inp_pegpool_pegdata64,
      String   inp_peglevel_hex
   );

   public static class Out_movecoins {
      public boolean out_ok;
      public String  out_src_pegdata64;
      public long    out_src_liquid;
      public long    out_src_reserve;
      public String  out_dst_pegdata64;
      public long    out_dst_liquid;
      public long    out_dst_reserve;
      public String  out_err;
   }
   public native Out_movecoins movecoins(
      long     inp_move_amount,
      String   inp_src_pegdata64,
      String   inp_dst_pegdata64,
      String   inp_peglevel_hex,
      boolean  inp_cross_cycles
   );
   public native Out_movecoins moveliquid(
      long     inp_move_amount,
      String   inp_src_pegdata64,
      String   inp_dst_pegdata64,
      String   inp_peglevel_hex
   );
   public native Out_movecoins movereserve(
      long     inp_move_amount,
      String   inp_src_pegdata64,
      String   inp_dst_pegdata64,
      String   inp_peglevel_hex
   );
 
   // TDD
   public static void main(String[] args) {
      System.out.println("getpeglevel: test1");
      Out_getpeglevel out1 = new pegops().getpeglevel(
         1,
         0,
         51,
         51,
         51,
         "",
         ""
      );
      System.out.println("getpeglevel: ok    :" + out1.out_ok);
      System.out.println("getpeglevel: hex   :" + out1.out_peglevel_hex);
      System.out.println("getpeglevel: pool  :" + out1.out_pegpool_pegdata64);
      System.out.println("getpeglevel: err   :" + out1.out_err);
      System.out.println("");

      System.out.println("updatepegbalances: test2");

      String pegpool_base64 = "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";
      String balance_base64 = "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";
      String peglevel_hex1 = "6e2d0000000000006d2d000000000000f700fa00fd00000000000000000000000000000000000000";
    
      Out_updatepegbalances out2 = new pegops().updatepegbalances(
         balance_base64,
         pegpool_base64,
         peglevel_hex1
      );

      System.out.println("updatepegbalances: ok       :" + out2.out_ok);
      System.out.println("updatepegbalances: balance  :" + out2.out_balance_pegdata64);
      System.out.println("updatepegbalances: balance L:" + out2.out_balance_liquid);
      System.out.println("updatepegbalances: balance R:" + out2.out_balance_reserve);
      System.out.println("updatepegbalances: pool     :" + out2.out_pegpool_pegdata64);
      System.out.println("updatepegbalances: err      :" + out2.out_err);
      System.out.println("");

      System.out.println("updatepegbalances: test3");

      pegpool_base64 = "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";
      balance_base64 = "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";
      String peglevel_hex2 = "6f2d0000000000006e2d000000000000f700fa00fd00000000000000000000000000000000000000";
    
      Out_updatepegbalances out3 = new pegops().updatepegbalances(
         balance_base64,
         pegpool_base64,
         peglevel_hex2
      );

      System.out.println("updatepegbalances: ok       :" + out3.out_ok);
      System.out.println("updatepegbalances: balance  :" + out3.out_balance_pegdata64);
      System.out.println("updatepegbalances: balance L:" + out3.out_balance_liquid);
      System.out.println("updatepegbalances: balance R:" + out3.out_balance_reserve);
      System.out.println("updatepegbalances: pool     :" + out3.out_pegpool_pegdata64);
      System.out.println("updatepegbalances: err      :" + out3.out_err);
      System.out.println("");

      System.out.println("movecoins: test4");
      String src_base64 = "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";
      String dst_base64 = "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";
      peglevel_hex2 = "6f2d0000000000006e2d000000000000f700fa00fd00000000000000000000000000000000000000";
    
      Out_movecoins out4 = new pegops().movecoins(
         1000L,
         src_base64,
         dst_base64,
         peglevel_hex2,
         true
      );

      System.out.println("movecoins: ok   :" + out4.out_ok);
      System.out.println("movecoins: src  :" + out4.out_src_pegdata64);
      System.out.println("movecoins: src L:" + out4.out_src_liquid);
      System.out.println("movecoins: src R:" + out4.out_src_reserve);
      System.out.println("movecoins: dst  :" + out4.out_dst_pegdata64);
      System.out.println("movecoins: dst L:" + out4.out_dst_liquid);
      System.out.println("movecoins: dst R:" + out4.out_dst_reserve);
      System.out.println("movecoins: err  :" + out4.out_err);
      System.out.println("");

      System.out.println("moveliquid: test5");
      src_base64 = "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";
      dst_base64 = "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";
      peglevel_hex2 = "6f2d0000000000006e2d000000000000f700fa00fd00000000000000000000000000000000000000";
    
      Out_movecoins out5 = new pegops().moveliquid(
         1000L,
         src_base64,
         dst_base64,
         peglevel_hex2
      );

      System.out.println("moveliquid: ok   :" + out5.out_ok);
      System.out.println("moveliquid: src  :" + out5.out_src_pegdata64);
      System.out.println("moveliquid: src L:" + out5.out_src_liquid);
      System.out.println("moveliquid: src R:" + out5.out_src_reserve);
      System.out.println("moveliquid: dst  :" + out5.out_dst_pegdata64);
      System.out.println("moveliquid: dst L:" + out5.out_dst_liquid);
      System.out.println("moveliquid: dst R:" + out5.out_dst_reserve);
      System.out.println("moveliquid: err  :" + out5.out_err);
      System.out.println("");

      System.out.println("movereserve: test6");
      src_base64 = "AgACAAAAAAAAAAAAZAgAAAAAAAB42u1Z93NVRRh9Ly+FF4IhAUKLICDVQYowEFTQgEMACdIkUhxDyQTpMgIBdAREmqgUpQsK0qvUgFJEkNCLotIEISAtlBBKIPfpu/cc5u2Z4Q9wJu+Xk6/s3t1vv7Yblyv/l//L/+X/8n/5v/zf/+VXOXrhqKD/sFv3mj7/LxL8+z7ntz3IoXeBjoL88PSZTf30RcgBroL443j2sQg/BoNf6LgzPiajd7ifzji52ebXiLlu+fk7MH9B6Cd7HbTAfwScW8bh54Ees3STjXO2ZNj8EIy/Cflf02LtoYXA9wDPZTW2VVfUXpPrl2/MdfQ57uWDdw17uIEXIS8A+kbX+1l+2lP9gM3Hsl3nDwYZdqbdKpzxRAbaNxx87q9zgx72ErEcH2dJCalnL+H4zlMX/Hzus3apq6F+rLvsqaKB59AuuqI9z6VWq+2pczDfxLc62UdStnGXMD/GXQo27LVoaB97voTM6bbgFvj9Yrbb85US/xiwe6Un8JxH1T7rDlw/7bR19jZbD2zfHeChhOIP/ZgFmvaujg1eEjs9AB192qE5zhJ7cT0PwXdjQRwfInFwXfyvgPhRKOjbsp5gsce2sZfsJSxJzLbtTjtEQ+8uaI98/yr4hUHHnW5mb4nrp160rNcr/kM/5XmHybpjQF8Teye23WNvKVz2TXv2PlDWCrQb7Z0nyJ/69z1Zn1v43GdG7WqewP1w3qegnw06paZDh8t5XRR/oJznsMnrNvKEW+zHdUe26RgceK5cR0KSHWauCLEr/eP9NsmewDikPRq2uWecL9c5sltbwx/PtXewRd/rIYH7YhxWPLXDpjNBt4RBcmSdQ+rE3Q88X8ojxocY/vY4bwPf6dTZ5vNcisp6ue88OTf6YWjKOMOuLonba1JHbovf35D49Mr6Lj/B76gfJnm+/sBY43y84v/kR0pchcp8tEchiXeut4ic9y3JJ7R/iU5p7kB/43zMh8wPpcG/IOspIPohsh637MfzhHygcRcpduZ8uZKvNC/w++EST5qPvXLeGj9Bsj+P7JN5tpj4U56Mvyf+dFPq0GXx6wJybrlip2DZj+qpHbIkX5eW/HJZ7H1H1hcm9vfK/LdE3yV17qHIfWKnwhK/audI+U6o2NsrdtHvZ4tekOgFy/d9Ege35Xx4flGVpgYF5nH6WYT47Z0n+DX3mSnnGybjomT/hUWu47JkPV6Jt0JSt89LXaLe06D/eUJd5zm8O+iRYTfmnQEPHxn1i+d1aGOesT7W0dM55ndo18nNU+f56T2gT0G+lP0pcCAmjEdgLIAe9YcCm/M8genSh3QDtsZ8RSDfApzNfQM/x/cOQ/47sJ7b9J8Z0OvHfAj5YshbsN9lvoWjLsC44eDvx/iSwNHAK5BXAZ2GcRNlvbRHb8i7gF4OrAXshPl2QO8R+J2lnoxxm9+vA5wDPIBxzzHuJX/tZHxYpn2vSD6YALoc6DdBNwJdGOuYAHoR5osFvzX7XmBbqRP9gT+I/78KbAmsAvnbwA3gz8X3WnE+yXNjwP8MOAK4CvJ4qVcngPswbxQEtVh/gDWg9yfos6Bb0e/Yl4E/C9gB/MXML/jOM/jOds9Ax18kPzCPR/nMdbFPaMC4AL2P8Y/5G0N/r2Xa8QOMew/0auitAJ06ym3024yvekl5Rj5ivzTotY7Ou4Bl5sNg/LEJer3AjwH9DeQnLNPP1wKToD9E8l1x4ALeuzB+veSRrxifoHNAHwN9VOKSeaEc5kmHfC79E/IlkJ+0zLjyyHk1hV4l7h/4G/jZcNhq9D/2wTWcDNlH7BZ50rH885IXxgJ7QO9b7q+K86HG4HNfEcwfvG+CfwzrSQMfzy0unn8xjGM+WAh+c9ihBuhUyJeLPZjvllvme0t5jFvJegea9vqD9YL3P+B01jXQR1zmOqeAXgl8Fvx7zA8Stx2Ba4C7eY7Qp33LAz8GNuK9U+r8COyTfQfr4jTQG6Xfy4D+Hex/JgIjxW2+E+RA7wuMPyp9QgLvs3KvYny+hHrXkHmI+4Fee3xvLeS/SD9XSvLH+mRHcZL0WZOYD5hPWactR3BE+irW6VWsJ8B1zFPsk3jf5Duf9E0X66EPBr8dsAPkY0A3A/038KBl9h9xfCd1m/7zNft/7YdAFxO/2495b7CfBt2NeQZxNwd0feZhiWfW+8rgL6M/AV/BvKx3kzVupH/dIX0Hnml9FdymHwfJeSdL/h0N3Mx6Jv0V6zTf83pKnY4FzmM+l77iNPiJvEfhO8Mg/wn8T6VfY19Bew6T82iDeWjX0XLPPMh3HyD7iVkYnyVxcwz0XtCsU6xn3dn3W6bfsg+YzToO+Xzw2e9+yHoL/AjzDRa/Zb4eLv3PFOiVAD2e/gx6J3A+9HphngTaGfImGNeE9w9guvTlVYEz2SdJnzXcba6jJft/8esy4ic/+sw+nXX5uMzP+K3EexyQ+YT+7JG+jf3RXJ9pL/rhGr73gf6EedYy3x+vyvsl94lnyMfjJ8i9KQ0OXUryN+8v7M/pF+WAW9kPir3HWeZ99pDkrS+lrsfLfaIC3/eBXYHdLbMvY/1nXmA8z2efAr0X+P8l9oNybozT7yWOWCebsi8AnoQ8SfyZ+0mQuPsV69wJmnluGPh9wY8nDfnPwBeBezHvILmv0n/Ky/drSf3cYJn1j+fbE99dL/3OA4mTW8xzcv7ZmJd+MBX4OnAz5HVBV5V3lJKSx+h/6+Q8EyRvvQEcDLyJeWryviJ9D+OOdao+78PAkS6zD+d9tLXYq4T4B9/LmF95X62Ieb5j/wi8Iv0H43Soz3xH6Cp1iPfBGcBdmH8r5MxfmeCnZ4ca/fikw05lTUl0G35XDAWoP/0TyL69zxn0d9tS7Sv5v8XopVBvLQAAAAAAAG4tAAAAAAAA9wD6AP0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEedIfDgEAAA==";
      dst_base64 = "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";
      peglevel_hex2 = "6f2d0000000000006e2d000000000000f700fa00fd00000000000000000000000000000000000000";
    
      Out_movecoins out6 = new pegops().movereserve(
         10000L,
         src_base64,
         dst_base64,
         peglevel_hex2
      );

      System.out.println("movereserve: ok   :" + out6.out_ok);
      System.out.println("movereserve: src  :" + out6.out_src_pegdata64);
      System.out.println("movereserve: src L:" + out6.out_src_liquid);
      System.out.println("movereserve: src R:" + out6.out_src_reserve);
      System.out.println("movereserve: dst  :" + out6.out_dst_pegdata64);
      System.out.println("movereserve: dst L:" + out6.out_dst_liquid);
      System.out.println("movereserve: dst R:" + out6.out_dst_reserve);
      System.out.println("movereserve: err  :" + out6.out_err);
      System.out.println("");
   }
}
