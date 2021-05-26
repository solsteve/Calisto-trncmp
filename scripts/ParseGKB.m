% 


function out = ParseGKB( outfile, infile )
  G = load( infile );

  num_pts = G.griddata.cell.npts;
  num_azm = G.deminfo.numang;

  fp = fopen( outfile, "w" );

  fprintf( fp, "%d %d\n", num_pts, num_azm );

  for gp = 1:num_pts
    gx   = G.griddata.xutm(gp,1);
    gy   = G.griddata.yutm(gp,1);
    gz   = G.griddata.altitude(gp,1);
    lat  = G.griddata.latlon(gp,1);
    lon  = G.griddata.latlon(gp,2);
    zone = G.griddata.utmzone;
    
    fprintf( fp, "%d %.3f %.3f %.3f %.6f %.6f\n", zone, gx, gy, gz, lat, lon );

    for wg = 1:num_azm
      radian    = G.deminfo.azimuths(wg);
      angle     = radian * 57.29577951308232;
      distance  = G.deminfo.distances(G.hrzndist(gp,wg));
      elevation = G.hrznalt(gp,wg);
      flag      = G.isbuilding(gp,wg);
      fprintf( fp, "%.4f %.3f %.3f %d\n", angle, distance, elevation, flag );
    end
  end

  fclose( fp );

  out = 0;
end
