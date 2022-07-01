<!-- Página que permite a troca de informação entre o arduino e a base de dados -->

<html>
<body>

    <?php
    // Definição das variaveis internas com a informação que vem na url 
    $Y0=$_GET["saidaY0"];
    $Y1=$_GET['saidaY1'];
    $Y2=$_GET['saidaY2'];
    $Y3=$_GET['saidaY3'];
    $Y4=$_GET['saidaY4'];
    $Y5=$_GET['saidaY5'];
    $Y6=$_GET['saidaY6'];
    $Y7=$_GET['motor'];
    $X1=$_GET['saidaX1'];
    $X2=$_GET['saidaX2'];
    $X3=$_GET['saidaX3'];
    $X4=$_GET['saidaX4'];
    $X5=$_GET['saidaX5'];
    $X6=$_GET['saidaX6'];
    $P1=$_GET['palete1'];
    $P2=$_GET['palete2'];
    $P3=$_GET['palete3'];
    $P4=$_GET['palete4'];
    $P5=$_GET['palete5'];
    $P6=$_GET['palete6'];
    $D=$_GET['distribuicao'];
    $S=$_GET['operacao'];
    $O=$_GET['start'];

 /* Conectando, escolhendo o banco de dados */
    $link = mysqli_connect("localhost", "root", "0000")or die("Não pude conectar: " . mysqli_error());
    mysqli_select_db($link,"psa") or die("Não pude selecionar o banco de dados");
 /* Query SQL de actualizacao */
    $query = "UPDATE estado SET Y0='" . $Y0 . "', Y1='" . $Y1 . "', Y2='" . $Y2 . "', Y3='" . $Y3 . "', Y4='" . $Y4 . "', Y5='" . $Y5 . "', Y6='" . $Y6 . "', Motor='" . $Y7 . "', X1='" . $X1 . "', X2='" . $X2 . "', X3='" . $X3 . "', X4='" . $X4 . "', X5='" . $X5 . "', X6='" . $X6 ."', Palete1='". $P1 ."', Palete2='". $P2 ."', Palete3='". $P3 ."', Palete4='". $P4 ."', Palete5='". $P5. "', Palete6='". $P6. "', Operacao='".$O."',Distribuicao='".$D."',Aguardar='".$S."' WHERE id=1";
    $result = mysqli_query($link,$query) or die("A query falhou: " . mysqli_error());
 /* Fazendo a query SQL DE LEITURA DA BASE DE DADOS*/
    $query = "SELECT * FROM estado";
    $result = mysqli_query($link,$query) or die("A query falhou: " . mysqli_error());
    $linha1=mysqli_fetch_array($result,MYSQLI_ASSOC);
    echo "#".$linha1['Palete'];
    echo "#".$linha1['Posicao'];
    echo "#".$linha1['Start'];
 /* Liberta o resultado */
    mysqli_free_result($result);
 /* Fechando a conexão */
    mysqli_close($link);
 
    ?>
</body>
</html>ç
