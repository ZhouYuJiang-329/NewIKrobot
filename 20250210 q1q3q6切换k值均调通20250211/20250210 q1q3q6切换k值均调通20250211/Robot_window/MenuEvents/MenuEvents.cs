using Robot_window.UI_Page;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows;
using Robot_window.ViewModels;
using RobotLibrary;
using System.Windows.Media.Media3D;
using HelixToolkit.Wpf;
using System.Windows.Media;
using PA.src;
using System.Threading;
using System.Security.Permissions;
using Microsoft.Win32;
using System.Windows.Input;
using System.Globalization;
using System.Security.AccessControl;
using System.IO;
using System.Windows.Documents;
using MathNet.Symbolics;
using MathNet.Numerics;
using ScottPlot;

namespace Robot_window.MenuEvents
{
    internal class MenuEvents
    {
        private HelixViewport3D viewPort3d ;

        public SerialPortUtils serialPortUtils = new SerialPortUtils();
        


        public PointsVisual3D Points = new PointsVisual3D
        {
            Color = System.Windows.Media.Colors.Red,
            Size = 4
        };
        public PointsVisual3D PathMovePoints = new PointsVisual3D()
        {
            Color = System.Windows.Media.Colors.Green,
            Size = 4
        };
        public ModelVisual3D toolmodelvisual= new ModelVisual3D();
        public GeometryModel3D toolmodel3d=null;
        public TranslateTransform3D tooltd;
        public MeshGeometry3D shijian;

        //生成笛卡尔轨迹列表
        internal List<CartesianPosition> CartesianPositions = new List<CartesianPosition>();
        public int CpCount = 0;
        // MoveL,MoveJ生成的路径点
        internal List<Position> MovePositions = new List<Position>();
        internal int MpCount = 0;
        public int ListBoxLidex = 0;
        //坐标系切换
        internal Frame frame1= new Frame() { Content = new JointMovePage() };
        internal Frame frame2=new Frame() { Content=new CartesianMovePage()};
        internal Frame frame3=new Frame() { Content=new FaLanMovepage()};
        public List<ModelVisual3D> modelVisual3Ds = new List<ModelVisual3D>();
        public int order = 3;//曲线拟合多项式阶数
        public double[] coefficients;

        public MenuEvents()
        {
            viewPort3d = MainWindow.mainwindow.viewPort3d;
            coefficients = new double[3*(order + 1)];
            //MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
        }
        public void JointSpace(object sender, RoutedEventArgs e)
        {
            frame1 = new Frame() { Content = new JointMovePage() };
            MainWindow.mainwindow.contentcon.Content = frame1;
        }

        public void CartesianSpace(object sender, RoutedEventArgs e)
        {
            frame2 = new Frame() { Content = new CartesianMovePage() };
           MainWindow.mainwindow. contentcon.Content = frame2;
        }

        public void FaLanSpace(object sender, RoutedEventArgs e)
        {
            var falan =new FaLanMovepage();
            falan.Inint();
            frame3 = new Frame() { Content = falan};
            MainWindow.mainwindow.contentcon.Content = frame3;
            
        }

        public void HanShuPath_Click(object sender, RoutedEventArgs e)
        {
            double a = 0.002734069064;
            double b = -1.811320754717;
            double tlast = 1.5;
            double jiange = 0.05;
         var HanShuPath=TrajectoryPlanning.HanShuPath(a, b, tlast, jiange);
            if (Points != null)
            {
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
            }
            foreach (CartesianPosition position in HanShuPath)
            {
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            }
            viewPort3d.Children.Add(Points);
            CartesianPositions = HanShuPath;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
        }
        //方形曲线
        public void GridPath_Click(object sender, RoutedEventArgs e)
        {
           
            List<CartesianPosition> gridpathpoints = new List<CartesianPosition>();
            GridPath gridPath = new GridPath();
            gridPath.ShowDialog();
            gridpathpoints = TrajectoryPlanning.GridPath(gridPath.StartPoint, gridPath.EndPoint, gridPath.DirVector, gridPath.width, gridPath.lenght, gridPath.re);
            if (Points != null)
            {
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
            }
            foreach (CartesianPosition position in gridpathpoints)
            {
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            }
            viewPort3d.Children.Add(Points);
            CartesianPositions = gridpathpoints;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
        }

        //圆柱体曲线
        public void RotunditPathWindow_Click(object sender, RoutedEventArgs e)
        {
            List<CartesianPosition> rotunditpathpoints = new List<CartesianPosition>();
            RotundityPathWindow rotundityPathWindow = new RotundityPathWindow();
            rotundityPathWindow.ShowDialog();
            rotunditpathpoints = TrajectoryPlanning.RotundityPath(rotundityPathWindow.COCircle, rotundityPathWindow.NormalVector, rotundityPathWindow.radius,
               rotundityPathWindow.length, rotundityPathWindow.length_num, rotundityPathWindow.round_num, rotundityPathWindow.posture, rotundityPathWindow.reverse);
            if (Points != null)
            {
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
            }
            foreach (CartesianPosition position in rotunditpathpoints)
            {
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            }
            viewPort3d.Children.Add(Points);
            CartesianPositions = rotunditpathpoints;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
        }

        //球体曲线
        public void SphericalPathWindow_Click(object sender, RoutedEventArgs e)
        {
            List<CartesianPosition> sphericapathpoints = new List<CartesianPosition>();
            SphericalPathWindow sphericalPathWindow = new SphericalPathWindow();
            sphericalPathWindow.ShowDialog();
            sphericapathpoints = TrajectoryPlanning.SphericalPath(sphericalPathWindow.COSphere, sphericalPathWindow.dirVector, sphericalPathWindow.radius,
            sphericalPathWindow.startrad, sphericalPathWindow.endrad, sphericalPathWindow.rad_num, sphericalPathWindow.round_num, 0, sphericalPathWindow.reverse);
            if (Points != null)
            {
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
            }
            foreach (CartesianPosition position in sphericapathpoints)
            {
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            }
            viewPort3d.Children.Add(Points);
            CartesianPositions = sphericapathpoints;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
        }

        //清空轨迹事件响应函数
        public void PathClick(object sender, RoutedEventArgs e)
        {
            if (Points != null)
            {
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = null;
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
                CpCount = 0;
                 MpCount = 0;
                CartesianPositions.Clear();
                MovePositions.Clear();
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            }
        }
        //复位机械臂
        public void ResetRobot(object sender, RoutedEventArgs e)
        {
            double[] angles = { 0, 0, 0, 0, 0, 0 };
            MainWindow.mainwindow. ForwardMove(angles);
            if (MainWindow.mainwindow.simulation == false)
                Control2183.Control2183.control.Command_2183(angles, MainWindow.mainwindow.Control2183Speed);
            if (MainWindow.mainwindow. contentcon.Content == frame1)
                JointMovePage.jointmovepage.Inint();
            else
                CartesianMovePage.cartesianmovpage.Inint();
            ListBoxLidex = 0;
        }

        public void Speedset(object sender, RoutedEventArgs e)
        {
            SpeedSetWindow speedSetWindow = new SpeedSetWindow();
            speedSetWindow.ShowDialog();

        }

            public void SerialPort(object sender, RoutedEventArgs e)
        {  
            List<int> deviceAddresses = new List<int> {1,1,2,2,3,3,4,4,5,5,6,6};

            serialPortUtils.LoadAddress(deviceAddresses);
            double[] angles = new double[6];
            Console.WriteLine("------------------");
            for (int i = 1; i < 7; i++)
            {

                //bool single = true;
                //serialPortUtils.StartPolling(single);
                //Thread.Sleep(200);
                //bool notsingle = false;
                //serialPortUtils.StartPolling(notsingle);
                //Thread.Sleep(200);

                bool single = true;
                double angle = 0;
                int numcircle = 0;
                serialPortUtils.StartPolling(single);
                Thread.Sleep(300);
                angle = serialPortUtils.Angle;
                serialPortUtils.Angle = 0;
                Console.WriteLine("angle：" + angle);
                Console.WriteLine("\n");
                single = false;
                serialPortUtils.StartPolling(single);
                Thread.Sleep(300);
                numcircle = serialPortUtils.NumCircle;
                //serialPortUtils.NumCircle = 0;
                Console.WriteLine("numcircle：" + numcircle);
                Console.WriteLine("\n");
                //if (MainWindow.mainwindow.simulation == false)
                    angles[i-1] = Control2183.Control2183.control.InitAngle(numcircle, angle, i);

            }
            //double[] angles1 = new double[6];//{ angles[1] , angles[0] , angles[2] , angles[3] , angles[4] , angles[5] };

            // 0 -0.0102 -3.8846 -0.423 -4.832 0

                //            0
                //- 0.0022
                //- 0.0446
                //0.4023
                //- 0.157
                //0


            angles[0] = angles[0] - 27.702064183091167;// 2 1 3 4 6 5
            angles[1] = angles[1] - 3.2096049802147761 + 0.0102 + 0.0022;
            angles[2] = -(angles[2] + 3.5820997933253178 + 3.8846 + 0.0446) ;
            angles[3] = -(angles[3] - 1.2262836216633357 + 0.423  -  0.4023);
            angles[4] = -(angles[4] + 51.505606840471515 + 4.832 + 0.157);
            angles[5] = -(angles[5] - 10.550751123530128);

            //耦合补偿
            angles[5] = angles[5] + 0.0125 * angles[4];

            
            MainWindow.mainwindow.OldAngles = angles;
            MainWindow.mainwindow.ForwardMove(angles);

            if (MainWindow.mainwindow. contentcon.Content == frame1)
                JointMovePage.jointmovepage.Inint();
            else
                CartesianMovePage.cartesianmovpage.Inint();

            //  bool single = false;
            //serialPortUtils.StartPolling(single);

            // Thread.Sleep(100);
            //  bool notsingle = true;
            //serialPortUtils.StartPolling(notsingle);
        }

        public void Control2183_init(object sender, RoutedEventArgs e)
        {
            Control2183.Control2183.control.Connect2183();
        }
        public void LinePathWindow_Click(object sender, RoutedEventArgs e)
        {
            LinePathWindow linePathWindow = new LinePathWindow();
            linePathWindow.ShowDialog();
            List<CartesianPosition> positions = new List<CartesianPosition>();
            CartesianPosition start = new CartesianPosition(linePathWindow.start_x, linePathWindow.start_y, linePathWindow.start_z, 
                linePathWindow.A_start, linePathWindow.B_start, linePathWindow.C_start);
            CartesianPosition end = new CartesianPosition(linePathWindow.end_x, linePathWindow.end_y, linePathWindow.end_z,
                linePathWindow.A_end, linePathWindow.B_end, linePathWindow.C_end); ;
            positions = TrajectoryPlanning.LinePath(start, end, linePathWindow.num);
            if (Points != null)
            {
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
            }
            foreach (CartesianPosition position in positions)
            {
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            }
            viewPort3d.Children.Add(Points);
            CartesianPositions = positions;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            //179.76 -3.07 90.01
        }

        public void toolset(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = "c:\\desktop";    //初始的文件夹
            openFileDialog.Filter = "STL Files (*.stl)|*.stl|OBJ Files (*.obj)|*.obj";//在对话框中显示的文件类型
            openFileDialog.FilterIndex = 2;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.ShowDialog();    //显示对话框
            string filepath = openFileDialog.FileName; //获取选择的文件的全路径名


            //加载模型
            var importer = new ModelImporter();
            var scene = importer.Load(filepath);
            toolmodel3d = scene.Children[0] as GeometryModel3D;
            toolmodel3d.Material= Materials.White;
            toolmodelvisual = new ModelVisual3D { Content = toolmodel3d };

            Transform3DGroup T = new Transform3DGroup();

         
            double[] angles = new double[6];
            double[] JointRad = BasicAlgorithm.AngleToRad(angles);
            JointPosition jointposition = new JointPosition(JointRad);
           
           var path=  PathClass.FKNewRad(JointRad);
            double[] frame = new double[3] { path.X * 1000, path.Y * 1000, path.Z * 1000 };
           tooltd = new TranslateTransform3D(frame[0], frame[1], frame[2]);

            //T.Children.Add(R);
            //T.Children.Add(R2);
            //T.Children.Add(td);
            toolmodel3d.Transform = tooltd;
            viewPort3d.Children.Add(toolmodelvisual);
            double[] angless = MainWindow.mainwindow.RightNowPosition.Joints.Joints.ToArray();
            int j=0;
            foreach (var i in angless)
            {
                angless[j] = i * 180 / Math.PI;
                j++;
            }
            MainWindow.mainwindow.ForwardMove(angless);
            
        }

        public void world3dclick(object sender, MouseButtonEventArgs e)
        {
            var mousePos = e.GetPosition(viewPort3d);
            var point3D = viewPort3d.Viewport.UnProject(mousePos);
            var his = viewPort3d.Viewport.FindHits(mousePos);
           
            if (his.Count > 0)
            {
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = null;
                var hit = his.First();
                var p = hit.Position;
                var index= FaceLocation(shijian, p);
                var t= FaVector(index);
               var rot= BasicAlgorithm.RotMatrixToRxyz(t);
                CartesianPosition carposition=new CartesianPosition(p.X, p.Y, p.Z, rot[0], rot[1], rot[2]);
                CartesianPositions.Add(carposition);
                var builder = new MeshBuilder(true, true);
               
                builder.AddSphere(p, 1);
                var g = new GeometryModel3D(builder.ToMesh(), Materials.Blue);
                ModelVisual3D v = new ModelVisual3D();
                v.Content = g;
                modelVisual3Ds.Add(v);
                viewPort3d.Children.Add(v);
                //MessageBox.Show($"X: {p.X}, Y: {p.Y}, Z: {p.Z}");
                //MainWindow.mainwindow.CartesianPositionList.
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            }
            else if (point3D.HasValue)
            {
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = null;
                // 获取的三维坐标
                var position2 = point3D.Value;
                if(position2.Z<0)
                    position2.Z = 0;
                //MessageBox.Show($"X: {position2.X}, Y: {position2.Y}, Z: {position2.Z}");
                CartesianPosition carposition = new CartesianPosition(position2.X, position2.Y, position2.Z, Math.PI, 0, 0);
                CartesianPositions.Add(carposition);
                var builder = new MeshBuilder(true, true);
                var position1 = new Point3D(position2.X, position2.Y, position2.Z);
                builder.AddSphere(position2, 10);
                var g = new GeometryModel3D(builder.ToMesh(), Materials.Blue);
                ModelVisual3D v = new ModelVisual3D();
                v.Content = g;
                modelVisual3Ds.Add(v);
                viewPort3d.Children.Add(v);
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;

            }
        }

        internal void clearworld(object sender, RoutedEventArgs e)
        {
            foreach (var item in modelVisual3Ds.ToArray()) // 使用ToArray()来避免在迭代过程中修改集合  
            {
                viewPort3d.Children.Remove(item);
            }
            ListBoxLidex = 0;
        }

        public void SpecimensProduce(object sender, RoutedEventArgs e)
        {
            RectAngleWindow rectAngleWindow = new RectAngleWindow();
            rectAngleWindow.ShowDialog();
            MeshBuilder builder = new MeshBuilder(true, true);
            builder.AddBox(rectAngleWindow.Point, rectAngleWindow.xlenght,rectAngleWindow.ylenght, rectAngleWindow.zlenght);
            GeometryModel3D model = new GeometryModel3D(builder.ToMesh(), Materials.White);

            shijian=builder.ToMesh();
            ModelVisual3D modelvisual = new ModelVisual3D();
            modelvisual.Content = model;
            viewPort3d.Children.Add(modelvisual);
        }

        private List<Point3D>  FaceLocation(MeshGeometry3D c,Point3D point)
        {
            double sumX = 0, sumY = 0, sumZ = 0;
            int vertexCount = c.Positions.Count;

            foreach (Point3D vertex in c.Positions)
            {
                sumX += vertex.X;
                sumY += vertex.Y;
                sumZ += vertex.Z;
            }

            double centerX = sumX / vertexCount;
            double centerY = sumY / vertexCount;
            double centerZ = sumZ / vertexCount;

            Point3D center = new Point3D(centerX, centerY, centerZ);

            double width = c.Bounds.SizeX;
            double height = c.Bounds.SizeY;
            double depth = c.Bounds.SizeZ;
            double tolerance = 0.1;
            int[] indexs= new int[3];
            List<Point3D> result = new List<Point3D>();
            if (Math.Abs((point.X-center.X) - width /2) < tolerance)
            {
                for (int i = 0;i<3;i++)
                {
                    indexs[i]=c.TriangleIndices[i];
                }
            }
            else if (Math.Abs((point.X-center.X) + width/2) < tolerance)
            {
                for (int i = 0; i < 3; i++)
                {
                    indexs[i] = c.TriangleIndices[6+i];
                }
            }
            else if (Math.Abs((point.Y-center.Y) - height/2) < tolerance)
            {
                for (int i = 0; i < 3; i++)
                {
                    indexs[i] = c.TriangleIndices[6*2 + i];
                }
            }
            else if (Math.Abs((point.Y-center.Y) + height/2) < tolerance)
            {
                for (int i = 0; i < 3; i++)
                {
                    indexs[i] = c.TriangleIndices[6*3 + i];
                }
            }
            else if (Math.Abs((point.Z - center.Z) - depth/2) < tolerance)
            {
                for (int i = 0; i < 3; i++)
                {
                    indexs[i] = c.TriangleIndices[6*4 + i];
                }
                
            }
            else if (Math.Abs((point.Z - center.Z) + depth/2) < tolerance)
            {
                for (int i = 0; i < 3; i++)
                {
                    indexs[i] = c.TriangleIndices[6 * 5  + i];
                }
            }
            else
            {
                Console.WriteLine("该点不在任何面上");
            }
            result.Add(c.Positions[indexs[0]]);
            result.Add(c.Positions[indexs[1]]);
            result.Add(c.Positions[indexs[2]]);
            return result;
        }
        private double[,] FaVector(List<Point3D> p)
        {
            Vector3D[] result = new Vector3D[p.Count];
            Vector3D v1 = p[1] - p[0];
            Vector3D v2 = p[2] - p[0];
            Vector3D v3= p[2] - p[1];
            Vector3D normal = Vector3D.CrossProduct(v1, v2);
            normal.Normalize(); // 可选：单位化
            v1.Normalize();
            v3.Normalize();
            result[0]=v3;
            result[1]=-v1;
            result[2] = -normal;
            double[,] R=new double[3,3];
            if (result[2].X == 1 || result[2].X == -1)
                result[0] = -result[0];
            for (int i = 0;i<3;i++)
                for (int j = 0;j<3;j++)
                {
                    
                    if(j==0)
                    R[j, i] = result[i].X;
                    if(j==1)
                        R[j, i] = result[i].Y;
                    if(j==2)
                        R[j, i] = result[i].Z;
                    
                }
            return R;
        }
       

        internal void DeskProduce(object sender, RoutedEventArgs e)
        {
            MeshBuilder builder = new MeshBuilder(true, true);
            Point3D center = new Point3D(600 - 280, 0, 0);
            double xlenght = 1200;
            double ylenght = 800;
            double zlenght = 50;
            builder.AddBox(center, xlenght, ylenght, zlenght);
            GeometryModel3D model = new GeometryModel3D(builder.ToMesh(), Materials.White);
            shijian = builder.ToMesh();
            ModelVisual3D modelvisual = new ModelVisual3D();
            modelvisual.Content = model;
            viewPort3d.Children.Add(modelvisual);
        }

        public void PointToPath_Click(object sender, RoutedEventArgs e)
        {
            List<CartesianPosition> gridpathpoints = new List<CartesianPosition>();
            PointToPathWindow pointToPathWindow = new PointToPathWindow();
            pointToPathWindow.ShowDialog();
            string filePath = "D:\\code\\华数机械臂\\RobotApp - 华数测试demo (3)\\RobotApp - 华数测试demo\\test.txt"; // 替换为您的文件路径
            var lines = File.ReadAllLines(filePath);

            List<CartesianPosition> positions = new List<CartesianPosition>();

            int pointnum = lines.Length / 4;

            double[,] R = new double[3, 3];

            double[] Rxyz = new double[3];

            double[] T = new double[3];
            
            for (int i = 0; i < lines.Length-32; i += 32) // 每个矩阵占用 4 行
            {
                //public static double[] RotMatrixToRxyz(double[,] R)
                for (int j = 0; j < 3; j++)
                {
                    var values = lines[i + j].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                                    .Select(v => double.Parse(v, CultureInfo.InvariantCulture))
                                    .ToArray();

                    R[j,0] = values[0];
                    R[j, 1] = values[1];
                    R[j, 2] = values[2];

                    T[j] = values[3];
                }
                Rxyz = BasicAlgorithm.RotMatrixToRxyz(R);
                T[0] = T[0] - 100;
                CartesianPosition temp = new CartesianPosition(T, Rxyz);

                positions.Add(temp);
            }

            CartesianPositions = positions;

            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
        }

        /// <summary>
        /// 三次样条插值，先给每个空间的点赋予时间，然后进行三次样条插值
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void ThreePath_Click(object sender, RoutedEventArgs e)
        {
            //每个点赋予时间
            for (int i = 0; i < CartesianPositions.Count; i++)
            {
                CartesianPositions[i].t = i;
            }
            //三次样条插值
           coefficients= TrajectoryPlanning.CurveFitting(CartesianPositions,order:3);
            List<CartesianPosition> positions = new List<CartesianPosition>();
            for (double i = 0; i <= CartesianPositions.Count-1; )
            {
                double x = coefficients[0] + coefficients[1] * i + coefficients[2] * i * i + coefficients[3] * i * i * i;
                double y = coefficients[4] + coefficients[5] * i + coefficients[6] * i * i + coefficients[7] * i * i * i;
                double z = coefficients[8] + coefficients[9] * i + coefficients[10] * i * i + coefficients[11] * i * i * i;
                double A = Math.PI;
                double B = 0;
                double C = 0;
                CartesianPosition temp = new CartesianPosition(x, y, z, A, B, C);
                temp.t = i;
                positions.Add(temp);
                i += 0.05;
            }
            CartesianPositions = positions;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            //显示路径点
            if (Points != null)
            {
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
            }
            foreach (CartesianPosition position in CartesianPositions)
            {
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            }
            viewPort3d.Children.Add(Points);
            
            //求出x,y,z的表达式
            PathClass.FunctionExpressionx= PathClass.FuncStringProduce(coefficients,0, order);
            PathClass.FunctionExpressiony = PathClass.FuncStringProduce(coefficients, 4, order);
            PathClass.FunctionExpressionz = PathClass.FuncStringProduce(coefficients, 8, order);
            Console.WriteLine("x表达式：" + PathClass.FunctionExpressionx);
            Console.WriteLine("y表达式：" + PathClass.FunctionExpressiony);
            Console.WriteLine("z表达式：" + PathClass.FunctionExpressionz);

            //计算q3表达式  此时已经得到了q3一系列点
            double[,] Q3 = PathClass.Q3Product(CartesianPositions);
            Q3Draw(Q3);
            //计算A6B6表达式
            double[,] A6B6 = PathClass.A6B6Product(CartesianPositions);
            A6B6Draw(A6B6);

            //计算q1-6表达式
            double[,] Q = PathClass.QProduct(CartesianPositions);
            // List<double> t = PathClass.TChange;
            List<double> t =new List<double>();
             t.Add(0.15);
            t.Add(0.25);
            t.Add(0.35);
            t.Add(0.45);
            int[] indexs = TChanglistToIndex(t);

            QDraw(Q, indexs);


           




        }

        public int[] TChanglistToIndex(List<double> t)
        {
            int[] index = new int[t.Count];
            for (int i = 0; i < t.Count; i++)
            {
                index[i] = CartesianPositions.FindIndex(p =>  Math.Abs(p.t-t[i])<=1e-6);
            }
            return index;
        }

        /// <summary>
        /// 显示A6B6的真实图和三次插值图,
        /// </summary>
        /// <param name="Q3"></param>
        public void Q3Draw(double[,] Q3)
        {
            chart2 chart3 = new chart2();
            chart3.Show();
            List<double> list_t = new List<double>();
            foreach (var position in CartesianPositions)
            {
                list_t.Add(position.t);
            }
            var ts = list_t.ToArray();
            var Q31 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据

            int columnsCount = Q3.GetLength(1); // 获取列数
            Q31 = Enumerable.Range(0, columnsCount)
                                       .Select(col => Q3[0, col])
                                       .ToArray();

            double[] Q3Coefficients = Fit.Polynomial(ts, Q31, 3);
            double[] Q3Value = new double[ts.Length];
            PathClass.Q3String = PathClass.FuncStringProduce(Q3Coefficients, 0, order);
                      
            Console.WriteLine("Q3表达式：" + PathClass.Q3String);
            
            int j = 0;
            foreach (var item in ts)
            {
                Q3Value[j] = PathClass.StringExpretion(PathClass.Q3String, item);
                j++;
            }
            chart3.pltshow(ts, Q31);
            chart3.SetlegendText("Q3true");
            chart3.pltshow(ts, Q3Value);
            chart3.SetlegendText("Q3nihe");
            chart3.SetLineStyle(LinePattern.Dotted);
            chart3.Set("Q3:" + PathClass.Q3String, "t", "Q3");
        }

        public void QDraw(double[,] Q, int[] orders)
        {
            chart2 chart3 = new chart2();
            chart3.Show();
            List<double> list_t = new List<double>();
            foreach (var position in CartesianPositions)
            {
                list_t.Add(position.t);
            }
            var ts = list_t.ToArray();
            var Q1 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据

            int columnsCount = Q.GetLength(1); // 获取列数
            Q1 = Enumerable.Range(0, columnsCount)
                                       .Select(col => Q[0, col])
                                       .ToArray();
            var Q2 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据
            Q2 = Enumerable.Range(0, columnsCount)
                                       .Select(col => Q[1, col])
                                       .ToArray();
            var Q3 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据
            Q3 = Enumerable.Range(0, columnsCount)
                                       .Select(col => Q[2, col])
                                       .ToArray();
            var Q4 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据
            Q4 = Enumerable.Range(0, columnsCount)
                                       .Select(col => Q[3, col])
                                       .ToArray();
            var Q5 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据
            Q5 = Enumerable.Range(0, columnsCount)
                                       .Select(col => Q[4, col])
                                       .ToArray();
            var Q6 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据
            Q6 = Enumerable.Range(0, columnsCount)
                                       .Select(col => Q[5, col])
                                       .ToArray();

            double[] Q1Coefficients = Fit.Polynomial(ts, Q1, 3);
            PathClass.Q1Value = new double[ts.Length];
            PathClass.Q1String = PathClass.FuncStringProduce(Q1Coefficients, 0, order);

            double[] Q2Coefficients = Fit.Polynomial(ts, Q2, 3);
            PathClass.Q2Value = new double[ts.Length];
            PathClass.Q2String = PathClass.FuncStringProduce(Q2Coefficients, 0, order);

            double[] Q3Coefficients = Fit.Polynomial(ts, Q3, 3);
            PathClass.Q3Value = new double[ts.Length];
            PathClass.Q3String = PathClass.FuncStringProduce(Q3Coefficients, 0, order);

            double[] Q4Coefficients = Fit.Polynomial(ts, Q4, 3);
            PathClass.Q4Value = new double[ts.Length];
            PathClass.Q4String = PathClass.FuncStringProduce(Q4Coefficients, 0, order);

            double[] Q5Coefficients = Fit.Polynomial(ts, Q5, 3);
            PathClass.Q5Value = new double[ts.Length];
            PathClass.Q5String = PathClass.FuncStringProduce(Q5Coefficients, 0, order);

            double[] Q6Coefficients = Fit.Polynomial(ts, Q6, 3);
            PathClass.Q6Value = new double[ts.Length];
            PathClass.Q6String = PathClass.FuncStringProduce(Q6Coefficients, 0, order);



            //Console.WriteLine("Q1表达式：" + PathClass.Q1String);

            int j = 0;
            foreach (var item in ts)
            {
                PathClass.Q1Value[j] = PathClass.StringExpretion(PathClass.Q1String, item);
                PathClass.Q2Value[j] = PathClass.StringExpretion(PathClass.Q2String, item);
                PathClass.Q3Value[j] = PathClass.StringExpretion(PathClass.Q3String, item);
                PathClass.Q4Value[j] = PathClass.StringExpretion(PathClass.Q4String, item);
                PathClass.Q5Value[j] = PathClass.StringExpretion(PathClass.Q5String, item);
                PathClass.Q6Value[j] = PathClass.StringExpretion(PathClass.Q6String, item);
                j++;
            }
       
            chart3.pltshowChange(ts, Q1, orders);
            chart3.SetlegendText("Q1true");
            chart3.pltshow(ts, PathClass.Q1Value);
            chart3.SetlegendText("Q1nihe");

            chart3.pltshow(ts, Q2);
            chart3.SetlegendText("Q2true");
            chart3.pltshow(ts, PathClass.Q2Value);
            chart3.SetlegendText("Q2nihe");

            chart3.pltshow(ts, Q3);
            chart3.SetlegendText("Q3true");
            chart3.pltshow(ts, PathClass.Q3Value);
            chart3.SetlegendText("Q3nihe");

            chart3.pltshow(ts, Q4);
            chart3.SetlegendText("Q4true");
            chart3.pltshow(ts, PathClass.Q4Value);
            chart3.SetlegendText("Q4nihe");

            chart3.pltshow(ts, Q5);
            chart3.SetlegendText("Q5true");
            chart3.pltshow(ts, PathClass.Q5Value);
            chart3.SetlegendText("Q5nihe");

            chart3.pltshow(ts, Q6);
            chart3.SetlegendText("Q6true");
            chart3.pltshow(ts, PathClass.Q6Value);
            chart3.SetlegendText("Q6nihe");


            //chart3.SetLineStyle(LinePattern.Dotted);
            chart3.Set("Q3:" + PathClass.Q3String, "t", "Q");
        }


        /// <summary>
        /// 显示A6B6的真实图和三次插值图,
        /// </summary>
        /// <param name="A6B6"></param>
        public void A6B6Draw(double[,] A6B6)
        {
            chart2 chart2 = new chart2();
            chart2.Show();
            List<double> list_t = new List<double>();
            foreach (var position in CartesianPositions)
            {
                list_t.Add(position.t);
            }
            var ts = list_t.ToArray();
            var A6 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据

            int columnsCount = A6B6.GetLength(1); // 获取列数
            A6 = Enumerable.Range(0, columnsCount)
                                       .Select(col => A6B6[0, col])
                                       .ToArray();
            var B6 = new double[ts.Length];
            // 使用 LINQ 获取指定行的数据
            B6 = Enumerable.Range(0, columnsCount)
                                      .Select(col => A6B6[1, col])
                                      .ToArray();

            double[] A6Coefficients = Fit.Polynomial(ts, A6, 3);
            double[] A6Value = new double[ts.Length];
            PathClass. A6String = PathClass.FuncStringProduce(A6Coefficients, 0, order);
            double[] B6Coefficients = Fit.Polynomial(ts, B6, 3);
            double[] B6Value = new double[ts.Length];
            PathClass. B6String = PathClass.FuncStringProduce(B6Coefficients, 0, order);
            Console.WriteLine("A6表达式：" + PathClass.A6String);
            Console.WriteLine("B6表达式：" + PathClass.B6String);
          
            int j = 0;
            foreach (var item in ts)
            {
                A6Value[j] = PathClass.StringExpretion(PathClass.A6String, item);
                B6Value[j] = PathClass.StringExpretion(PathClass.B6String, item);
                j++;
            }
            chart2.pltshow(ts, A6);
            chart2.SetlegendText("A6true");
            chart2.pltshow(ts, A6Value);
            chart2.SetlegendText("A6nihe");
            chart2.SetLineStyle(LinePattern.Dotted);
            chart2.Set("A6:"+ PathClass.A6String + " B6:"+ PathClass.B6String, "t", "A6");

            chart2.pltshow(ts, B6);
            chart2.SetlegendText("B6true");
            chart2.pltshow(ts, B6Value);
            chart2.SetlegendText("B6nihe");
            chart2.SetLineStyle(LinePattern.Dashed);

        }



       

        //private void test22()
        //{

        //    string filePath = "D:\\test.txt"; // 替换为您的文件路径
        //    var lines = File.ReadAllLines(filePath);

        //    Position temp = new Position(new double[] { 0.02, 0.02, 0.02, 0.02, 0.02, 0.02 }, _arm, Grip2Tool);


        //    //PathClass path1 = new PathClass(ArmType.GP7);

        //    int pointnum = lines.Length / 4;
        //    for (int i = 0, k = count; i < lines.Length; k++, i += 4) // 每个矩阵占用 4 行
        //    {
        //        PathClass path1 = new PathClass(_arm);


        //        for (int j = 0; j < 3; j++)
        //        {
        //            var values = lines[i + j].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
        //                            .Select(v => double.Parse(v, CultureInfo.InvariantCulture))
        //                            .ToArray();

        //            path1.eerot[j * 3] = values[0];
        //            path1.eerot[j * 3 + 1] = values[1];
        //            path1.eerot[j * 3 + 2] = values[2];

        //            path1.eetrans[j] = values[3] / 1000;
        //        }

        //        //if (tool != 0)
        //        //{
        //        //    path1.Matrix2T();


        //        //    path1.T2Matrix(path1.RT * Tool2Grip);
        //        //    //矩阵相乘
        //        //    //path1.T = Matrix.Multiply(path1.T, tool_t);


        //        //    //path1.eetrans[0] -= 0.095;
        //        //    //path1.eetrans[2] -= 0.063;
        //        //}


        //        path1.IK(Tool2Grip);



        //        PathClass.FindNearest(temp.joints, path1);

        //        temp = new Position(path1.joints, _arm, Grip2Tool);
        //        if (k >= MaxSize)
        //        {
        //            pathss[k - MaxSize] = temp;
        //        }
        //        else
        //        {
        //            pathss[k] = temp;
        //        }


        //        CountStop++;

        //    }
        //}
    }
}
