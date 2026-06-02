using HelixToolkit.Wpf;
using MathNet.Numerics;
using MathNet.Symbolics;
using Microsoft.Win32;
using PA.src;
using Robot_window.UI_Page;
using Robot_window.ViewModels;
using RobotLibrary;
using ScottPlot;
using ScottPlot.Plottables;
using System;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics.Contracts;
using System.Globalization;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Security.Policy;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Media3D;
using static FParsec.ErrorMessage;
using static SkiaSharp.HarfBuzz.SKShaper;
//using RLDemo;
//using System.Linq;
using RLDemo;

namespace Robot_window.MenuEvents
{
    internal class MenuEvents
    {
        private HelixViewport3D viewPort3d;

        public SerialPortUtils serialPortUtils = new SerialPortUtils();

        public PointsVisual3D PathPoints = new PointsVisual3D()
        {
            Color = System.Windows.Media.Colors.Red,
            Size = 3
        };
        public PointsVisual3D NewIKPathPoints = new PointsVisual3D()
        {
            Color = System.Windows.Media.Colors.Black,
        };
        public PointsVisual3D PathMovePoints = new PointsVisual3D()
        {
            Color = System.Windows.Media.Colors.Green,
            Size = 3
        };
        public PointsVisual3D Points = new PointsVisual3D
        {
            Color = System.Windows.Media.Colors.Red,
            Size = 6
        };
        public ModelVisual3D toolmodelvisual = new ModelVisual3D();
        public GeometryModel3D toolmodel3d = null;
        public TranslateTransform3D tooltd;
        public MeshGeometry3D shijian;

        internal List<CartesianPosition> CartesianPositions = new List<CartesianPosition>();
        public int CpCount = 0;
        public int CpTotalCount = 0;

        internal List<Position> MovePositions = new List<Position>();
        internal int MpCount = 0;
        public int ListBoxLidex = 0;
        public BaiDongSao sanjiaobaidong = new BaiDongSao();

        internal Frame frame1 = new Frame() { Content = new JointMovePage() };
        internal Frame frame2 = new Frame() { Content = new CartesianMovePage() };
        internal Frame frame3 = new Frame() { Content = new FaLanMovepage() };

        public List<ModelVisual3D> modelVisual3Ds = new List<ModelVisual3D>();

        public Vector3D planeNormal = new Vector3D();
        public int order = 3;
        public double[] coefficients;

        public int dibo_shixu_biaoding = 700;
        public int dibo_fengzhi_biaoding = 121;
        List<Position> MovePositions_chazhi = new List<Position>();
        private int _calibrationClickCount = 0;

        private RLInference _rl;
        private AgentController _agent;
        private Thread _rlThread;
        private volatile bool _rlStop;
        private const int GRID_SIZE = 64;
        private const int HW_SETTLE_MS = 300;
        private const int CONTROL_PERIOD_MS = 200;
        private const int START_SKIP = 70;
        private const int WINDOW_SIZE = 900;      
        private float _echoMaxEma = 250f;          
        private const float ECHO_EMA_ALPHA = 0.1f; 


        private readonly object _echoLock = new object();
        private volatile bool _stopPipeReader = false; 

        private EventWaitHandle _globalEventWaitHandle = new EventWaitHandle(false, EventResetMode.AutoReset, "Global\\MyEvent");

        private string roughDataPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, $"RoughSearch_RawData_{DateTime.Now:yyyyMMdd_HHmmss}.csv");
        private List<double[]> roughPoseList = new List<double[]>();
        private List<double[]> roughWaveList = new List<double[]>();

        private string rlDataPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, $"RLSearch_RawData_{DateTime.Now:yyyyMMdd_HHmmss}.csv");
        private List<double[]> rlPoseList = new List<double[]>();
        private List<double[]> rlWaveList = new List<double[]>();
        private readonly object _rlCsvLock = new object();

        private static (float rx, float ry, float rz) ApplyDeltaRzRad(float rxRad, float ryRad, float rzRad, float deltaRzRad)
        {
            double c1 = Math.Cos(rzRad), s1 = Math.Sin(rzRad);
            double c2 = Math.Cos(ryRad), s2 = Math.Sin(ryRad);
            double c3 = Math.Cos(rxRad), s3 = Math.Sin(rxRad);

            double r11 = c1 * c2;
            double r12 = c1 * s2 * s3 - s1 * c3;
            double r13 = c1 * s2 * c3 + s1 * s3;
            double r21 = s1 * c2;
            double r22 = s1 * s2 * s3 + c1 * c3;
            double r23 = s1 * s2 * c3 - c1 * s3;
            double r31 = -s2;
            double r32 = c2 * s3;
            double r33 = c2 * c3;

            double cd = Math.Cos(deltaRzRad), sd = Math.Sin(deltaRzRad);

            double n11 = r11 * cd + r12 * sd;
            double n12 = -r11 * sd + r12 * cd;
            double n13 = r13;
            double n21 = r21 * cd + r22 * sd;
            double n22 = -r21 * sd + r22 * cd;
            double n23 = r23;
            double n31 = r31 * cd + r32 * sd;
            double n32 = -r31 * sd + r32 * cd;
            double n33 = r33;

            double newRy = -Math.Asin(n31);
            double newRx, newRz;
            if (Math.Abs(n31) < 0.999999)
            {
                double cosY = Math.Cos(newRy);
                newRx = Math.Atan2(n32 / cosY, n33 / cosY);
                newRz = Math.Atan2(n21 / cosY, n11 / cosY);
            }
            else
            {
                newRz = 0;
                if (n31 <= -1)
                {
                    newRy = Math.PI / 2;
                    newRx = Math.Atan2(-n23, -n13);
                }
                else
                {
                    newRy = -Math.PI / 2;
                    newRx = Math.Atan2(n23, n13);
                }
            }
            return ((float)newRx, (float)newRy, (float)newRz);
        }


        private void WriteColumnarCSV(string filePath, List<double[]> poseList, List<double[]> waveList)
        {
            try
            {
                using var writer = new StreamWriter(filePath, false);
                int numSteps = poseList.Count;
                int totalRows = 1024;
                for (int row = 0; row < totalRows; row++)
                {
                    var parts = new List<string>();
                    for (int s = 0; s < numSteps; s++)
                    {
 
                        if (poseList[s].Length <= row || waveList[s].Length <= row)
                        {
                            parts.Add("");
                            parts.Add("");
                            continue;
                        }
                        parts.Add(row < 6 ? poseList[s][row].ToString("F6") : "");
                        parts.Add(waveList[s][row].ToString("F2"));
                    }
                    writer.WriteLine(string.Join(",", parts));
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("error：" + ex.Message);
            }
        }

        private void AppendRLDataToCSV(double[] poseRecord, double[] waveRecord)
        {
            lock (_rlCsvLock)
            {
                rlPoseList.Add(poseRecord);
                rlWaveList.Add(waveRecord);
                WriteColumnarCSV(rlDataPath, rlPoseList, rlWaveList);
            }
        }

        internal void Gan_kong(object sender, RoutedEventArgs e)
        {
            roughDataPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, $"RoughSearch_{DateTime.Now:yyyyMMdd_HHmmss}.csv");
            rlDataPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, $"RLSearch_{DateTime.Now:yyyyMMdd_HHmmss}.csv");

            roughPoseList.Clear(); roughWaveList.Clear();
            rlPoseList.Clear(); rlWaveList.Clear();

            Thread thread = new Thread(gankongThread) { IsBackground = true };
            thread.Start();
        }

        public void Qiang_hua_xue_xi(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Gan_kong() ");
        }

        public void gankongThread()
        {
            List<Position> position_yisidian = new List<Position>();
            Console.WriteLine("C# process is waiting for the event...");

            try
            {

                foreach (var p_all in MovePositions_chazhi)
                {
                    if (p_all.Pose.X > 100)
                    {
                        p_all.Pose.X *= 0.001; p_all.Pose.Y *= 0.001; p_all.Pose.Z *= 0.001;
                    }

                    var angle = BasicAlgorithm.RadToAngle(p_all.Joints.Joints.ToArray());
                    App.Current.Dispatcher.Invoke(() => MainWindow.mainwindow.ForwardMove_xiancheng(angle));

                    if (!MainWindow.mainwindow.simulation)
                    {
                        Control2183.Control2183.control.Command_2183(angle, MainWindow.mainwindow.Control2183Speed);
                        Thread.Sleep(500);
                        lock (_echoLock) { MainWindow.mainwindow.RightNowPosition.ChaoSheng = null; }
                        _globalEventWaitHandle.Reset();
                        Control2183.Control2183.control.SendVirtualX(1500);
                        bool syncSuccess = _globalEventWaitHandle.WaitOne(2000);
                        if (!syncSuccess) Console.WriteLine("error：time out！");
                    }

                    int[] rawWave;
                    lock (_echoLock)
                    {
                        rawWave = MainWindow.mainwindow.RightNowPosition.ChaoSheng ?? Array.Empty<int>();
                    }
                    int[] newArray1 = rawWave.Skip(70).ToArray();
                    var max_bofeng1 = newArray1.Length > 0
                        ? newArray1.Select((value, index) => new { Value = value, Index = index }).Aggregate((a, b) => a.Value > b.Value ? a : b)
                        : new { Value = 0, Index = 0 };

                    if (max_bofeng1.Value > dibo_fengzhi_biaoding && max_bofeng1.Index < dibo_shixu_biaoding && max_bofeng1.Index > 300)
                    {
                        p_all.ChaoSheng_max = max_bofeng1.Value;
                        position_yisidian.Add(p_all);
                    }
                }

                if (position_yisidian.Count == 0)
                {
                    Console.WriteLine("over");
                    return;
                }


                Position globalTarget = position_yisidian.OrderByDescending(p => p.ChaoSheng_max).First();

    
                string onnxPath = @"E:\project\1121\onnx_models\ultrasound_navigation_model_600K.onnx";
                _rl ??= new RLInference(onnxPath);
                _agent ??= new AgentController(_rl, GRID_SIZE, 1f, randomStart: false) { XNormDenom = GRID_SIZE - 1, YNormDenom = GRID_SIZE - 1 };

                App.Current.Dispatcher.Invoke(() => { MessageBox.Show("RL start"); });

   
                foreach (var p in position_yisidian)
                {
                    var p_start = p;
                    var p_target = globalTarget;

                    var currentJoints = MainWindow.mainwindow.RightNowPosition.Joints;
                    var startIkResult = PathClass.IK(currentJoints, p_start.Pose);
                    var angleStart = BasicAlgorithm.RadToAngle(startIkResult.Joints.Joints.ToArray());

                    App.Current.Dispatcher.Invoke(() => MainWindow.mainwindow.ForwardMove_xiancheng(angleStart));

                    if (!MainWindow.mainwindow.simulation)
                    {
                        Control2183.Control2183.control.Command_2183(angleStart, MainWindow.mainwindow.Control2183Speed);
                        Thread.Sleep(2000);
                    }

                    _rlStop = false;
                    _rlThread = new Thread(() => { RLThread(p_start, p_target); }) { IsBackground = true };
                    _rlThread.Start();
                    while (_rlThread.IsAlive && !_rlStop) Thread.Sleep(200);
                }

                Console.WriteLine("\n🎉 RL search finished.");
            }
            catch (Exception ex)
            {
                App.Current.Dispatcher.Invoke(() => { MessageBox.Show("gankongThread : " + ex.Message); });
            }
        }

        private void RLThread(Position startPoint, Position optimalTarget)
        {
            double maxRLOffsetXY = 0.015;
            const float BASE_RX = (float)Math.PI;
            const float BASE_RY = 0f;

            double x_step = (maxRLOffsetXY * 2) / (GRID_SIZE - 1);
            double y_step = (maxRLOffsetXY * 2) / (GRID_SIZE - 1);

            (float rx, float ry, float rz) ApplyDeltaRz(float rxRad, float ryRad, float rzRad, float deltaRzRad)
            {
                double c1 = Math.Cos(rzRad), s1 = Math.Sin(rzRad);
                double c2 = Math.Cos(ryRad), s2 = Math.Sin(ryRad);
                double c3 = Math.Cos(rxRad), s3 = Math.Sin(rxRad);
                double r11 = c1 * c2, r12 = c1 * s2 * s3 - s1 * c3, r13 = c1 * s2 * c3 + s1 * s3;
                double r21 = s1 * c2, r22 = s1 * s2 * s3 + c1 * c3, r23 = s1 * s2 * c3 - c1 * s3;
                double r31 = -s2, r32 = c2 * s3, r33 = c2 * c3;
                double cd = Math.Cos(deltaRzRad), sd = Math.Sin(deltaRzRad);
                double n11 = r11 * cd + r12 * sd, n12 = -r11 * sd + r12 * cd, n13 = r13;
                double n21 = r21 * cd + r22 * sd, n22 = -r21 * sd + r22 * cd, n23 = r23;
                double n31 = r31 * cd + r32 * sd, n32 = -r31 * sd + r32 * cd, n33 = r33;
                double newRy = -Math.Asin(n31);
                double newRx, newRz;
                if (Math.Abs(n31) < 0.999999)
                {
                    double cosY = Math.Cos(newRy);
                    newRx = Math.Atan2(n32 / cosY, n33 / cosY);
                    newRz = Math.Atan2(n21 / cosY, n11 / cosY);
                }
                else
                {
                    newRz = 0;
                    if (n31 <= -1) { newRy = Math.PI / 2; newRx = Math.Atan2(-n23, -n13); }
                    else { newRy = -Math.PI / 2; newRx = Math.Atan2(n23, n13); }
                }
                return ((float)newRx, (float)newRy, (float)newRz);
            }

            _agent.SetPosition(GRID_SIZE / 2, GRID_SIZE / 2);
            _agent.CurrentRx = 0f; _agent.CurrentRy = 0f; _agent.CurrentRz = 0f;

            int step = 0;
            const int MAX_STEPS = 120;

            float initialRawPeak = ReadRawPeak();
            float bestRawPeak = initialRawPeak;
            bool hasGradient = false;

            List<double[]> explorationData = new List<double[]>();

            var initialIk = NewIK.IK_New_wuqiudao(startPoint.Pose, MainWindow.mainwindow.GripToTool);
            var currentTheoreticalJointsObj = initialIk.Joints;

            float startRz = (float)startPoint.Pose.RZ;
            float optRz = (float)optimalTarget.Pose.RZ;
            float diffRz = optRz - startRz;
            while (diffRz > Math.PI) diffRz -= (float)(2 * Math.PI);
            while (diffRz < -Math.PI) diffRz += (float)(2 * Math.PI);

            Random rnd = new Random();
            double smoothNoiseX = 0, smoothNoiseY = 0;
            float smoothNoiseRz = 0;

            try
            {
                while (!_rlStop && step < MAX_STEPS)
                {
                    float echoNorm = ReadEcho01();         
                    float rawPeak = ReadRawPeak();            

                    float[] obs = _agent.BuildModelInput(echoNorm, fiveDim: true);
                    float[] rawAction = _rl.GetContinuousAction(obs);
                    float[] scaledAction = ScaleAction(rawAction);
                    _agent.StepContinuous(scaledAction);

                    if (_agent.CurrentRz > 15f) _agent.CurrentRz = 15f;
                    else if (_agent.CurrentRz < -15f) _agent.CurrentRz = -15f;

                    var (gx, gy) = _agent.GetPosition();
                    float rlDeltaRzDeg = _agent.CurrentRz;

                    float progress = Math.Min(1.0f, step / 100.0f);

                    smoothNoiseX = 0.7 * smoothNoiseX + 0.3 * (rnd.NextDouble() * 2 - 1.0);
                    smoothNoiseY = 0.7 * smoothNoiseY + 0.3 * (rnd.NextDouble() * 2 - 1.0);
                    smoothNoiseRz = 0.7f * smoothNoiseRz + 0.3f * (float)(rnd.NextDouble() * 2 - 1.0);

                    double envelopeXY = 0.006 * (1.0 - progress);
                    float envelopeRz = 0.35f * (1.0f - progress);

                    double guidedX = startPoint.Pose.X + (optimalTarget.Pose.X - startPoint.Pose.X) * progress;
                    double guidedY = startPoint.Pose.Y + (optimalTarget.Pose.Y - startPoint.Pose.Y) * progress;
                    float guidedRz = startRz + diffRz * progress;

                    double exploreX = guidedX + smoothNoiseX * envelopeXY;
                    double exploreY = guidedY + smoothNoiseY * envelopeXY;
                    float exploreRz = guidedRz + smoothNoiseRz * envelopeRz;

                    double rlOffsetX = (gx - GRID_SIZE / 2) * x_step;
                    double rlOffsetY = (gy - GRID_SIZE / 2) * y_step;
                    float rlOffsetRzRad = (float)(rlDeltaRzDeg * Math.PI / 180.0);

                    var (rx, ry, rz) = ApplyDeltaRz(BASE_RX, BASE_RY, exploreRz, rlOffsetRzRad);
                    CartesianPosition target = new CartesianPosition
                    {
                        X = exploreX + rlOffsetX,
                        Y = exploreY + rlOffsetY,
                        Z = startPoint.Pose.Z,
                        RX = rx,
                        RY = ry,
                        RZ = rz
                    };

                    if (rawPeak > bestRawPeak)
                    {
                        bestRawPeak = rawPeak;
                 
                        if (rawPeak - initialRawPeak >= 5.0f) hasGradient = true;
                        Console.WriteLine($"New best raw echo: {rawPeak:F3}");
                    }

                    if (gx <= 1 || gx >= GRID_SIZE - 2 || gy <= 1 || gy >= GRID_SIZE - 2)
                        _agent.SetPosition(GRID_SIZE / 2, GRID_SIZE / 2);

                    var ikResult = PathClass.IK(currentTheoreticalJointsObj, target);
                    currentTheoreticalJointsObj = ikResult.Joints;
                    var angles = BasicAlgorithm.RadToAngle(currentTheoreticalJointsObj.Joints.ToArray());

                    Application.Current.Dispatcher.Invoke(() => MainWindow.mainwindow.ForwardMove(angles));

                    if (!MainWindow.mainwindow.simulation)
                    {
                        Control2183.Control2183.control.Command_2183(angles, MainWindow.mainwindow.Control2183Speed);
                        Thread.Sleep(HW_SETTLE_MS);
                        lock (_echoLock) { MainWindow.mainwindow.RightNowPosition.ChaoSheng = null; }
                        _globalEventWaitHandle.Reset();
                        Control2183.Control2183.control.SendVirtualX(1500);
                        _globalEventWaitHandle.WaitOne(500);
                    }
                    else Thread.Sleep(CONTROL_PERIOD_MS);

                    explorationData.Add(new double[] { target.X, target.Y, target.Z, target.RX, target.RY, target.RZ, echoNorm });

                    if (step % 20 == 0) Console.WriteLine($"RL step {step}/{MAX_STEPS}");
                    step++;
                }

                if (!hasGradient && bestRawPeak < 50.0f)
                    Console.WriteLine("No effective gradient found, best raw peak low.");
                else
                    Console.WriteLine("Gradient found, optimization finished.");


                if (explorationData.Count > 0)
                {
                    lock (_rlCsvLock)
                    {
                        using (StreamWriter sw = new StreamWriter(rlDataPath, true))
                        {
                            foreach (var d in explorationData)
                                sw.WriteLine($"{d[0]:F5},{d[1]:F5},{d[2]:F5},{d[3]:F5},{d[4]:F5},{d[5]:F5},{d[6]:F2}");
                        }
                    }
                }

                _rlStop = true;
            }
            catch (Exception ex)
            {
                Application.Current.Dispatcher.Invoke(() => { MessageBox.Show("RLThread异常: " + ex.Message); });
                _rlStop = true;
            }
        }

        private float[] ScaleAction(float[] action)
        {
            if (action == null || action.Length < 6) return new float[6];
            return new float[]
            {
                action[0] * 1.2f,
                action[1] * 1.2f,
                0f,
                action[3] * 5f,
                action[4] * 5f,
                action[5] * 5f
            };
        }

        private float ReadEcho01()
        {
            int rawMax = ReadRawPeak();

            _echoMaxEma = ECHO_EMA_ALPHA * rawMax + (1 - ECHO_EMA_ALPHA) * _echoMaxEma;
            if (_echoMaxEma < 1f) _echoMaxEma = 250f; 
            return Math.Clamp((float)rawMax / _echoMaxEma, 0f, 1f);
        }

        private int ReadRawPeak()
        {
            int[] wave;
            lock (_echoLock)
            {
                wave = MainWindow.mainwindow.RightNowPosition.ChaoSheng ?? Array.Empty<int>();
            }
            int len = wave.Length;
            if (len <= START_SKIP) return 0;
            int takeAvail = Math.Max(0, len - START_SKIP);
            int take = Math.Min(WINDOW_SIZE, takeAvail);
            if (take <= 0) return 0;
            return wave.Skip(START_SKIP).Take(take).Max();
        }

        public MenuEvents()
        {
            viewPort3d = MainWindow.mainwindow.viewPort3d;
        }

        public void JointSpace(object sender, RoutedEventArgs e)
        {
            frame1 = new Frame() { Content = new JointMovePage() };
            MainWindow.mainwindow.contentcon.Content = frame1;
        }

        public void CartesianSpace(object sender, RoutedEventArgs e)
        {
            frame2 = new Frame() { Content = new CartesianMovePage() };
            MainWindow.mainwindow.contentcon.Content = frame2;
        }

        public void FaLanSpace(object sender, RoutedEventArgs e)
        {
            var falan = new FaLanMovepage();
            falan.Inint();
            frame3 = new Frame() { Content = falan };
            MainWindow.mainwindow.contentcon.Content = frame3;
        }

        public void PathPointsProduce()
        {
            var moveLPoints = Position.MoveL(MainWindow.mainwindow.RightNowPosition, CartesianPositions[0].mmTom(), 0.5, MainWindow.mainwindow.GripToTool);
            for (int i = 1; i < CartesianPositions.Count; i++)
            {
                var list = Position.MoveL(moveLPoints[moveLPoints.Count - 1], CartesianPositions[i].mmTom(), 0.5, MainWindow.mainwindow.GripToTool);
                foreach (var p in list) moveLPoints.Add(p);
            }
            foreach (var p in moveLPoints)
            {
                PathPoints.Points.Add(new Point3D(p.Pose.X * 1000, p.Pose.Y * 1000, p.Pose.Z * 1000));
            }
        }

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
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            viewPort3d.Children.Add(Points);
            CartesianPositions = gridpathpoints;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            PathPointsProduce();
            viewPort3d.Children.Add(PathPoints);
        }

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
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            viewPort3d.Children.Add(Points);
            CartesianPositions = rotunditpathpoints;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            PathPointsProduce();
            viewPort3d.Children.Add(PathPoints);
        }

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
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            viewPort3d.Children.Add(Points);
            CartesianPositions = sphericapathpoints;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            PathPointsProduce();
            viewPort3d.Children.Add(PathPoints);
        }

        public void PathClick(object sender, RoutedEventArgs e)
        {
            MainWindow.mainwindow.CartesianPositionList.SelectionChanged -= MainWindow.mainwindow.CartesianPositionList_SelectionChanged;
            if (Points != null)
            {
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = null;
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
                CpCount = 0;
                MpCount = 0;
                CartesianPositions.Clear();
                viewPort3d.Children.Remove(PathMovePoints);
                MovePositions.Clear();
                viewPort3d.Children.Remove(PathPoints);
                PathPoints.Points.Clear();
                PathPoints.Children.Clear();
                viewPort3d.Children.Remove(NewIKPathPoints);
                NewIKPathPoints.Points.Clear();
                NewIKPathPoints.Children.Clear();
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
                MainWindow.mainwindow.CartesianPositionList.SelectionChanged += MainWindow.mainwindow.CartesianPositionList_SelectionChanged;
            }
        }

        public void ResetRobot(object sender, RoutedEventArgs e)
        {
            double[] angles = { 0, 0, 0, 0, 90, 0 };
            MainWindow.mainwindow.ForwardMove(angles);
            if (!MainWindow.mainwindow.simulation)
                Control2183.Control2183.control.Command_2183(angles, MainWindow.mainwindow.Control2183Speed);
            if (MainWindow.mainwindow.contentcon.Content == frame1)
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

            List<int> deviceAddresses = new List<int> { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6 };
            serialPortUtils.LoadAddress(deviceAddresses);
            double[] angles = new double[6];
            Console.WriteLine("------------------");
            for (int i = 1; i < 7; i++)
            {
                bool single = true;
                double angle = 0;
                int numcircle = 0;
                serialPortUtils.StartPolling(single);
                Thread.Sleep(300);
                angle = serialPortUtils.Angle;
                serialPortUtils.Angle = 0;
                Console.WriteLine("angle：" + angle);
                single = false;
                serialPortUtils.StartPolling(single);
                Thread.Sleep(300);
                numcircle = serialPortUtils.NumCircle;
                Console.WriteLine("numcircle：" + numcircle);
                angles[i - 1] = Control2183.Control2183.control.InitAngle(numcircle, angle, i);
            }
            angles[0] = angles[0] - 27.702064183091167;
            angles[1] = angles[1] - 3.2096049802147761 + 0.0102 + 0.0022;
            angles[2] = -(angles[2] + 3.5820997933253178 + 3.8846 + 0.0446);
            angles[3] = -(angles[3] - 1.2262836216633357 + 0.423 - 0.4023);
            angles[4] = -(angles[4] + 51.505606840471515 + 4.832 + 0.157);
            angles[5] = -(angles[5] - 10.550751123530128);
            angles[5] = angles[5] + 0.0125 * angles[4];
            MainWindow.mainwindow.OldAngles = angles;
            MainWindow.mainwindow.ForwardMove(angles);
            if (MainWindow.mainwindow.contentcon.Content == frame1)
                JointMovePage.jointmovepage.Inint();
            else
                CartesianMovePage.cartesianmovpage.Inint();
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
                linePathWindow.A_end, linePathWindow.B_end, linePathWindow.C_end);
            positions = TrajectoryPlanning.LinePath(start, end, linePathWindow.num);
            if (Points != null)
            {
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
            }
            foreach (CartesianPosition position in positions)
                Points.Points.Add(new Point3D(position.X, position.Y, position.Z));
            viewPort3d.Children.Add(Points);
            CartesianPositions = positions;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            PathPointsProduce();
            viewPort3d.Children.Add(PathPoints);
        }

        public void toolset(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = "c:\\desktop";
            openFileDialog.Filter = "OBJ Files (*.obj)|*.obj|STL Files (*.stl)|*.stl";
            openFileDialog.FilterIndex = 2;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.ShowDialog();
            string filepath = openFileDialog.FileName;
            var importer = new ModelImporter();
            var scene = importer.Load(filepath);
            toolmodel3d = scene.Children[0] as GeometryModel3D;
            toolmodel3d.Material = Materials.White;
            toolmodelvisual = new ModelVisual3D { Content = toolmodel3d };
            double[] angles = new double[6];
            double[] JointRad = BasicAlgorithm.AngleToRad(angles);
            JointPosition jointposition = new JointPosition(JointRad);
            PathClass path = new PathClass(jointposition);
            path.FK(MainWindow.mainwindow.GripToTool);
            double[] frame = new double[3] { path.Points.X * 1000, path.Points.Y * 1000, path.Points.Z * 1000 };
            tooltd = new TranslateTransform3D(frame[0], frame[1], frame[2]);
            toolmodel3d.Transform = tooltd;
            viewPort3d.Children.Add(toolmodelvisual);
            double[] angless = MainWindow.mainwindow.RightNowPosition.Joints.Joints.ToArray();
            for (int j = 0; j < angless.Length; j++) angless[j] = angless[j] * 180 / Math.PI;
            MainWindow.mainwindow.ForwardMove(angless);
        }

        public static double[,] GetRotationMatrix(Vector3D normal)
        {
            normal.Normalize();
            Vector3D a = Math.Abs(normal.X) < 1e-6 && Math.Abs(normal.Y) < 1e-6 ? new Vector3D(0, 1, 0) : new Vector3D(0, 0, 1);
            Vector3D u = Vector3D.CrossProduct(a, normal); u.Normalize();
            Vector3D v = Vector3D.CrossProduct(normal, u); v.Normalize();
            return new double[3, 3] { { u.X, v.X, normal.X }, { u.Y, v.Y, normal.Y }, { u.Z, v.Z, normal.Z } };
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
                List<Point3D> points_index = new List<Point3D>();
                CartesianPosition carposition = new CartesianPosition();
                if (shijian != null)
                {
                    points_index = FaceLocation(shijian, p);
                    var t = FaVector(points_index);
                    var rot = BasicAlgorithm.RotMatrixToRxyz(t);
                    carposition = new CartesianPosition(p.X, p.Y, p.Z, rot[0], rot[1], rot[2]);
                }
                else
                {
                    var rot = GetRotationMatrix(planeNormal);
                    var ro = BasicAlgorithm.RotMatrixToRxyz(rot);
                    carposition = new CartesianPosition(p.X, p.Y, p.Z, ro[0], ro[1], ro[2]);
                }
                CartesianPositions.Add(carposition);
                var builder = new MeshBuilder(true, true);
                builder.AddSphere(p, 1);
                var g = new GeometryModel3D(builder.ToMesh(), Materials.Blue);
                ModelVisual3D v = new ModelVisual3D();
                v.Content = g;
                modelVisual3Ds.Add(v);
                viewPort3d.Children.Add(v);
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            }
            else if (point3D.HasValue)
            {
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = null;
                var position2 = point3D.Value;
                if (position2.Z < 0) position2.Z = 0;
                CartesianPosition carposition = new CartesianPosition(position2.X, position2.Y, position2.Z, Math.PI, 0, 0);
                CartesianPositions.Add(carposition);
                var builder = new MeshBuilder(true, true);
                builder.AddSphere(new Point3D(carposition.X, carposition.Y, carposition.Z), 10);
                var g = new GeometryModel3D(builder.ToMesh(), Materials.Blue);
                ModelVisual3D v = new ModelVisual3D();
                v.Content = g;
                modelVisual3Ds.Add(v);
                viewPort3d.Children.Add(v);
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            }
            if (PathPoints.Points.Count != 0)
            {
                PathPoints.Points.Clear();
                PathPoints.Children.Clear();
                viewPort3d.Children.Remove(PathPoints);
            }
            PathPointsProduce();
            viewPort3d.Children.Add(PathPoints);
        }

        internal void clearworld(object sender, RoutedEventArgs e)
        {
            foreach (var item in modelVisual3Ds.ToArray())
                viewPort3d.Children.Remove(item);
            ListBoxLidex = 0;
        }

        public void SpecimensProduce(object sender, RoutedEventArgs e)
        {
            RectAngleWindow rectAngleWindow = new RectAngleWindow();
            rectAngleWindow.ShowDialog();
            MeshBuilder builder = new MeshBuilder(true, true);
            builder.AddBox(rectAngleWindow.Point, rectAngleWindow.xlenght, rectAngleWindow.ylenght, rectAngleWindow.zlenght);
            GeometryModel3D model = new GeometryModel3D(builder.ToMesh(), Materials.White);
            shijian = builder.ToMesh();
            ModelVisual3D modelvisual = new ModelVisual3D();
            modelvisual.Content = model;
            viewPort3d.Children.Add(modelvisual);
        }

        private List<Point3D> FaceLocation(MeshGeometry3D c, Point3D point)
        {
            double sumX = 0, sumY = 0, sumZ = 0;
            foreach (Point3D vertex in c.Positions) { sumX += vertex.X; sumY += vertex.Y; sumZ += vertex.Z; }
            Point3D center = new Point3D(sumX / c.Positions.Count, sumY / c.Positions.Count, sumZ / c.Positions.Count);
            double width = c.Bounds.SizeX, height = c.Bounds.SizeY, depth = c.Bounds.SizeZ;
            double tolerance = 0.1;
            int[] indexs = new int[3];
            List<Point3D> result = new List<Point3D>();
            if (Math.Abs((point.X - center.X) - width / 2) < tolerance)
                for (int i = 0; i < 3; i++) indexs[i] = c.TriangleIndices[i];
            else if (Math.Abs((point.X - center.X) + width / 2) < tolerance)
                for (int i = 0; i < 3; i++) indexs[i] = c.TriangleIndices[6 + i];
            else if (Math.Abs((point.Y - center.Y) - height / 2) < tolerance)
                for (int i = 0; i < 3; i++) indexs[i] = c.TriangleIndices[6 * 2 + i];
            else if (Math.Abs((point.Y - center.Y) + height / 2) < tolerance)
                for (int i = 0; i < 3; i++) indexs[i] = c.TriangleIndices[6 * 3 + i];
            else if (Math.Abs((point.Z - center.Z) - depth / 2) < tolerance)
                for (int i = 0; i < 3; i++) indexs[i] = c.TriangleIndices[6 * 4 + i];
            else if (Math.Abs((point.Z - center.Z) + depth / 2) < tolerance)
                for (int i = 0; i < 3; i++) indexs[i] = c.TriangleIndices[6 * 5 + i];
            else Console.WriteLine("any");
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
            Vector3D v3 = p[2] - p[1];
            Vector3D normal = Vector3D.CrossProduct(v1, v2);
            normal.Normalize();
            v1.Normalize();
            v3.Normalize();
            result[0] = v3;
            result[1] = -v1;
            result[2] = -normal;
            double[,] R = new double[3, 3];
            if (result[2].X == 1 || result[2].X == -1) result[0] = -result[0];
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                {
                    if (j == 0) R[j, i] = result[i].X;
                    if (j == 1) R[j, i] = result[i].Y;
                    if (j == 2) R[j, i] = result[i].Z;
                }
            return R;
        }

        internal void DeskProduce(object sender, RoutedEventArgs e)
        {
            MeshBuilder builder = new MeshBuilder(true, true);
            Point3D center = new Point3D(600 - 280, 0, 0);
            builder.AddBox(center, 1200, 800, 50);
            GeometryModel3D model = new GeometryModel3D(builder.ToMesh(), Materials.White);
            shijian = builder.ToMesh();
            ModelVisual3D modelvisual = new ModelVisual3D();
            modelvisual.Content = model;
            viewPort3d.Children.Add(modelvisual);
        }

        public void PointToPath_Click(object sender, RoutedEventArgs e)
        {
            PointToPathWindow pointToPathWindow = new PointToPathWindow();
            pointToPathWindow.ShowDialog();
            string filePath = "D:\\code\\RobotApp\\RobotApp\\test.txt";
            var lines = File.ReadAllLines(filePath);
            List<CartesianPosition> positions = new List<CartesianPosition>();
            double[,] R = new double[3, 3];
            double[] T = new double[3];
            for (int i = 0; i < lines.Length - 32; i += 32)
            {
                for (int j = 0; j < 3; j++)
                {
                    var values = lines[i + j].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                                    .Select(v => double.Parse(v, CultureInfo.InvariantCulture)).ToArray();
                    R[j, 0] = values[0]; R[j, 1] = values[1]; R[j, 2] = values[2];
                    T[j] = values[3];
                }
                var Rxyz = BasicAlgorithm.RotMatrixToRxyz(R);
                T[0] -= 100;
                positions.Add(new CartesianPosition(T, Rxyz));
            }
            CartesianPositions = positions;
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            PathPointsProduce();
            viewPort3d.Children.Add(PathPoints);
        }

        public void clearrobot(object sender, RoutedEventArgs e)
        {
            MainWindow.mainwindow.viewPort3d.Children.Remove(MainWindow.mainwindow.visual);
            MainWindow.mainwindow.visual.Content = null;
            MainWindow.mainwindow.ListJoints.Clear();
        }

        public void LoadRobot(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.DefaultExt = ".folder";
            dialog.Filter = "STL|*.stl";
            dialog.Multiselect = false;
            dialog.ShowDialog();
            string path = "";
            if (dialog.FileName != "")
            {
                string filePath = dialog.FileName;
                path = GetDirectoryPath(filePath);
            }
            RobotParams robotParams = new RobotParams();
            RobotLoad load = new RobotLoad();
            robotParams.LinkBasePath = path;
            MainWindow.mainwindow.RobotModel = load.StlLoad(robotParams.LinkBasePath);
            MainWindow.mainwindow.visual.Content = MainWindow.mainwindow.RobotModel;
            MainWindow.mainwindow.viewPort3d.Children.Add(MainWindow.mainwindow.visual);
            string[] files = Directory.GetFiles(path);
            string robotJointsParams = "";
            foreach (string file in files) if (file.Contains(".txt")) robotJointsParams = file;
            robotParams.RobotParamsRead(robotJointsParams);
            MainWindow.mainwindow.ListJoints = Joint.LoadParams(robotParams.robotparams);
            double[] angles = { 0, 0, 0, 0, 90, 0 };
            MainWindow.mainwindow.ForwardMove(angles);
        }

        private static string GetDirectoryPath(string filePath)
        {
            int lastSeparatorIndex = filePath.LastIndexOf(Path.DirectorySeparatorChar);
            return lastSeparatorIndex > 0 ? filePath.Substring(0, lastSeparatorIndex) : filePath;
        }

        public void SearchCom(object sender, RoutedEventArgs e)
        {
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
        }

        public void KeyDownSpace(object sender, KeyEventArgs e)
        {
            viewPort3d.Children.Remove(MainWindow.mainwindow.rectangleVisual3D);
            viewPort3d.Children.Remove(MainWindow.mainwindow.sphere);
            viewPort3d.Children.Remove(MainWindow.mainwindow.coordinateSystem);
        }

        public void ChartWindow_Click(object sender, RoutedEventArgs e)
        {
            List<double> list_t = new List<double>();
            double k = 0;
            for (int i = 0; i < MovePositions.Count; i++) { list_t.Add(k); k += 0.05; }
            double[] t = list_t.ToArray();
            double[] xFit = new double[MovePositions.Count];
            double[] xTrue = new double[MovePositions.Count];
            double[] yFit = new double[MovePositions.Count];
            double[] yTrue = new double[MovePositions.Count];
            double[] zFit = new double[MovePositions.Count];
            double[] zTrue = new double[MovePositions.Count];
            for (int i = 0; i < MovePositions.Count; i++)
            {
                xFit[i] = MovePositions[i].Pose.X * 1000;
                xTrue[i] = PathMovePoints.Points[i].X;
                yFit[i] = MovePositions[i].Pose.Y * 1000;
                yTrue[i] = PathMovePoints.Points[i].Y;
                zFit[i] = MovePositions[i].Pose.Z * 1000;
                zTrue[i] = PathMovePoints.Points[i].Z;
            }
            Error_Mse(xTrue, xFit, "X");
            Error_Mse(yTrue, yFit, "Y");
            Error_Mse(zTrue, zFit, "Z");
            Chart chart = new Chart();
            chart.Show();
            chart.pltshow(t, xFit); chart.SetlegendText("XFit");
            chart.pltshow(t, xTrue); chart.SetlegendText("XTrue");
            chart.pltshow(t, yFit); chart.SetlegendText("YFit");
            chart.pltshow(t, yTrue); chart.SetlegendText("YTrue");
            chart.pltshow(t, zFit); chart.SetlegendText("ZFit");
            chart.pltshow(t, zTrue); chart.SetlegendText("ZTrue");
        }

        private void Error_Mse(double[] xreal, double[] xfit, string name)
        {
            double mse = 0, maxerror = 0;
            for (int i = 0; i < xreal.Length; i++)
            {
                maxerror = Math.Max(maxerror, Math.Abs(xreal[i] - xfit[i]));
                mse += (xreal[i] - xfit[i]) * (xreal[i] - xfit[i]);
            }
            mse /= xreal.Length;
            Console.WriteLine($"MSE {name}: {mse}");
            Console.WriteLine($"MaxError {name}: {maxerror} mm");
        }

        public void ThreePath_Click(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < CartesianPositions.Count; i++) CartesianPositions[i].t = i;
            coefficients = TrajectoryPlanning.CurveFitting(CartesianPositions, 3);
            List<CartesianPosition> positions = new List<CartesianPosition>();
            for (double i = 0; i <= CartesianPositions.Count - 1; i += 0.05)
            {
                double x = coefficients[0] + coefficients[1] * i + coefficients[2] * i * i + coefficients[3] * i * i * i;
                double y = coefficients[4] + coefficients[5] * i + coefficients[6] * i * i + coefficients[7] * i * i * i;
                double z = coefficients[8] + coefficients[9] * i + coefficients[10] * i * i + coefficients[11] * i * i * i;
                CartesianPosition temp = new CartesianPosition(x, y, z, Math.PI, 0, 0) { t = i };
                positions.Add(temp);
            }
            if (MainWindow.mainwindow.NewIKFlag)
            {
                CartesianPositions = positions;
                MainWindow.mainwindow.CartesianPositionList.ItemsSource = CartesianPositions;
            }
            if (NewIKPathPoints != null)
            {
                viewPort3d.Children.Remove(NewIKPathPoints);
                NewIKPathPoints.Points.Clear();
            }
            foreach (CartesianPosition pos in CartesianPositions)
                NewIKPathPoints.Points.Add(new Point3D(pos.X, pos.Y, pos.Z));
            viewPort3d.Children.Add(NewIKPathPoints);
            NewIK.FunctionExpressionx = SymbolDerivation.FuncStringProduce(coefficients, 0, order);
            NewIK.FunctionExpressiony = SymbolDerivation.FuncStringProduce(coefficients, 4, order);
            NewIK.FunctionExpressionz = SymbolDerivation.FuncStringProduce(coefficients, 8, order);
            Console.WriteLine($"x: {NewIK.FunctionExpressionx}\ny: {NewIK.FunctionExpressiony}\nz: {NewIK.FunctionExpressionz}");
            double[,] Q3 = NewIK.Q3Product(CartesianPositions);
            double[,] Q = NewIK.QProduct(CartesianPositions);
        }

        public void Q6Draw_Click(object sender, RoutedEventArgs e)
        {
            double[,] Q3 = NewIK.Q3Product(CartesianPositions);
            Chart.Q3Draw(Q3, CartesianPositions);
            double[,] Q = NewIK.QProduct(CartesianPositions);
            List<double> t = new List<double> { 0.15, 0.25, 0.35, 0.45 };
            int[] indexs = NewIK.TChanglistToIndex(t, CartesianPositions);
            Chart.QDraw(Q, indexs, CartesianPositions);
        }

        public void A6B6Draw_Click(object sender, RoutedEventArgs e)
        {
            double[,] A6B6 = NewIK.A6B6Product(CartesianPositions);
            Chart.A6B6Draw(A6B6, CartesianPositions);
        }
        internal void Grep(object sender, RoutedEventArgs e)
        {
            _stopPipeReader = false;
            Thread thread = new Thread(WorkMethod) { IsBackground = true };
            thread.Start();
            Console.WriteLine("Pipe reader started.");
        }

        private void WorkMethod(object? obj)
        {
            while (!_stopPipeReader)
            {
                using (var pipeClient = new NamedPipeClientStream(".", "MyPipe", PipeDirection.In))
                {
                    try
                    {
                        pipeClient.Connect(1000); 
                        int[] array = null;
                        using (var reader = new BinaryReader(pipeClient))
                        {
                            try
                            {
                                int arraySize = reader.ReadInt32();
                                array = new int[arraySize];
                                for (int i = 0; i < arraySize; i++) array[i] = reader.ReadInt32();
                            }
                            catch (EndOfStreamException) { }
                            if (array != null)
                            {
                                lock (_echoLock) { MainWindow.mainwindow.RightNowPosition.ChaoSheng = array; }
                                Console.WriteLine($"xyz: {MainWindow.mainwindow.RightNowPosition.Pose.X} {MainWindow.mainwindow.RightNowPosition.Pose.Y} {MainWindow.mainwindow.RightNowPosition.Pose.Z}");
                                try
                                {
                                    var waitHandle = new EventWaitHandle(false, EventResetMode.AutoReset, "Global\\MyEvent");
                                    waitHandle.Set();
                                }
                                catch (Exception ex) { Console.WriteLine("WorkMethod: " + ex.Message); }
                            }
                        }
                    }
                    catch (TimeoutException) { /*  */ 
                    catch (Exception ex) { Console.WriteLine("Pipe error: " + ex.Message); }
                }
                Thread.Sleep(100); 
            }
            Console.WriteLine("Pipe reader stopped.");
        }

        internal void Calibration(object sender, RoutedEventArgs e)
        {
            _calibrationClickCount++;
            Console.WriteLine("Calibration...");
            CartesianPosition calibPose = new CartesianPosition
            {
                X = 0.63163,
                Y = 0.1538,
                Z = 0.112,
                RX = Math.PI,
                RY = 0,
                RZ = -175.2 * Math.PI / 180.0
            };
            var calibIkResult = NewIK.IK_New_wuqiudao(calibPose, MainWindow.mainwindow.GripToTool);
            var calibAngles = BasicAlgorithm.RadToAngle(calibIkResult.Joints.Joints.ToArray());
            App.Current.Dispatcher.Invoke(() => MainWindow.mainwindow.ForwardMove_xiancheng(calibAngles));
            if (!MainWindow.mainwindow.simulation)
            {
                Control2183.Control2183.control.Command_2183(calibAngles, MainWindow.mainwindow.Control2183Speed);
                Thread.Sleep(1500);
                _globalEventWaitHandle.Reset();
                Control2183.Control2183.control.SendVirtualX(1500);
                Console.WriteLine("trigger");
                bool syncSuccess = _globalEventWaitHandle.WaitOne(2000);
                if (!syncSuccess) Console.WriteLine("time out！");
            }
            int rawPeak = ReadRawPeak();
            float normalized = Math.Clamp((float)rawPeak / _echoMaxEma, 0f, 1f);
            Console.WriteLine($"Raw peak: {rawPeak}, normalized: {normalized:F3}");
            if (_calibrationClickCount == 3)
            {
                Console.WriteLine("Raising Z by 20mm...");
                try
                {
                    if (MovePositions_chazhi == null || MovePositions_chazhi.Count == 0)
                    {
                        MessageBox.Show("MovePositions_chazhi is empty. Please generate a path first.");
                        _calibrationClickCount--;
                        return;
                    }
                    var startPose = MovePositions_chazhi.First().Pose;
                    CartesianPosition raisePose = new CartesianPosition
                    {
                        X = startPose.X,
                        Y = startPose.Y,
                        Z = startPose.Z + 0.02,
                        RX = startPose.RX,
                        RY = startPose.RY,
                        RZ = startPose.RZ
                    };
                    var ikRaise = NewIK.IK_New_wuqiudao(raisePose, MainWindow.mainwindow.GripToTool);
                    var anglesRaise = BasicAlgorithm.RadToAngle(ikRaise.Joints.Joints.ToArray());
                    App.Current.Dispatcher.Invoke(() => MainWindow.mainwindow.ForwardMove_xiancheng(anglesRaise));
                    if (!MainWindow.mainwindow.simulation)
                    {
                        Control2183.Control2183.control.Command_2183(anglesRaise, MainWindow.mainwindow.Control2183Speed);
                        Thread.Sleep(1000);
                    }
                    _calibrationClickCount = 0;
                }
                catch (Exception ex) { Console.WriteLine("Calibration raise failed: " + ex.Message); }
            }
        }

        public List<CartesianPosition> Cycle(Position RightNowPosition, double r, int pointsCount)
        {
            List<CartesianPosition> result = new List<CartesianPosition>();
            for (int i = 0; i < pointsCount; i++)
            {
                double theta = 2 * Math.PI * i / pointsCount;
                double x = RightNowPosition.Pose.X + r * Math.Cos(theta);
                double y = RightNowPosition.Pose.Y + r * Math.Sin(theta);
                result.Add(new CartesianPosition(x, y, RightNowPosition.Pose.Z,
                    RightNowPosition.Pose.RX, RightNowPosition.Pose.RY, RightNowPosition.Pose.RZ));
            }
            return result;
        }

        internal void Grep2(object sender, RoutedEventArgs e)
        {
            Console.WriteLine($"xyz: {MainWindow.mainwindow.RightNowPosition.Pose.X} {MainWindow.mainwindow.RightNowPosition.Pose.Y} {MainWindow.mainwindow.RightNowPosition.Pose.Z}");
            Console.WriteLine("Received array:");
            foreach (var item in MainWindow.mainwindow.RightNowPosition.ChaoSheng) Console.Write(item + " ");
            Console.WriteLine();
        }

        public void ZhanMen() { }

        public void SanJiaoPath(object sender, RoutedEventArgs e)
        {
            if (MovePositions != null) MovePositions.Clear();
            if (MovePositions_chazhi != null) MovePositions_chazhi.Clear();
            sanjiaobaidong.SanJiaoSanGe = true;
            GridPath gridPath = new GridPath();
            gridPath.ShowDialog();
            var gridPoints = TrajectoryPlanning.GridPath(gridPath.StartPoint, gridPath.EndPoint, gridPath.DirVector, gridPath.width, gridPath.lenght, gridPath.re);
            if (Points != null)
            {
                viewPort3d.Children.Remove(Points);
                Points.Points.Clear();
            }
       
            List<CartesianPosition> mainPath = new List<CartesianPosition>();
            for (int ii = 0; ii < gridPoints.Count; ii++)
                if (ii % 2 == 0) mainPath.Add(gridPoints[ii]);
            CartesianPositions = gridPoints;
            int count = 0;
            List<Position> moveLPoints = new List<Position>();
            for (int idx = 0; idx < mainPath.Count - 1; idx++)
            {
                var segment = Position.MoveLNew(mainPath[idx].mmTom(), mainPath[idx + 1].mmTom(), 0.8, MainWindow.mainwindow.GripToTool);
                moveLPoints.AddRange(segment);
            }
            MovePositions = moveLPoints;
            int stepCounter = 0;
            foreach (var p in MovePositions)
            {
                stepCounter++;
                MovePositions_chazhi.Add(p);
                if (stepCounter == sanjiaobaidong.numstep)
                {
                    double[] angles = BasicAlgorithm.RadToAngle(p.Joints.Joints.ToArray());
                    var swing = sanjiaobaidong.GenerateReciprocatingSwing(angles);
                    MovePositions_chazhi.AddRange(swing);
                    stepCounter = 0;
                }
            }
            foreach (Position pos in MovePositions_chazhi)
                Points.Points.Add(new Point3D(pos.Pose.X * 1000, pos.Pose.Y * 1000, pos.Pose.Z * 1000));
            viewPort3d.Children.Add(Points);
            MainWindow.mainwindow.CartesianPositionList.ItemsSource = MovePositions_chazhi;
        }
    }
}
